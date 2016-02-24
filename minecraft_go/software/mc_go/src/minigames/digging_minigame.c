/*
 * digging_minigame.c
 *
 *  Created on: February 9, 2016
 *  Updated on: February 9, 2016
 *      Author: Logan
 */

#include <stdlib.h>
#include <stdio.h>
#include "serial.h"
#include "touchscreen.h"
#include "minigames.h"
#include "Colours.h"
#include "graphics.h"
#include "block.h"

/* Starting health per block type */
static int block_type_starting_health[BLOCK_TYPE_NUM_TYPES] =
{
		0, /* BLOCK_TYPE_DEAD */
		3, /* BLOCK_TYPE_WOOD */
		6, /* BLOCK_TYPE_STONE */
		10,	/* BLOCK_TYPE_IRON */
		14 /* BLOCK_TYPE_DIAMOND */
};

//increases the effectiveness of tools
#define WOOD_BUFF 1
#define STONE_BUFF 2
#define IRON_BUFF 4
#define DIAMOND_BUFF 6

//x coordinate for grid
#define X_COORD_INIT 40
#define X_COORD_INCREMENT 240

//y coordinate for grid
#define Y_COORD_INIT 0
#define Y_COORD_INCREMENT 240

//length of the sides of digging minigame boxes
#define BOX_SIZE 240
#define GRID_WIDTH 720
#define GRID_HEIGHT 480

/* Static Functions */
static boolean digging_minigame_main();
static int digging_minigame_generate_block_material();
static int digging_minigame_get_pickaxe_material();
static void digging_minigame_block_initialize(Box *box, int x, int y, block_type_t block_type);
static void digging_minigame_draw_block(int x, int y, block_type_t block_type, int health);
static void digging_minigame_damage_block(Box *box, int damage);
static boolean digging_minigame_is_done(Box array[2][3]);


boolean minigame_digging() {
	DEBUG("Digging minigame started!\n");

	/* Initialize everything */
	touchscreen_init();

	/* Clear the screen */
	graphics_clear_screen();

	/* Start the game */
	return digging_minigame_main();
}

/*
 * Gets the health of the blocks based on the material type
 */
static boolean digging_minigame_main() {
	int i, j;
	Box gridArray[2][3];
	Pixel touch;
	Pixel box;

	int damage = digging_minigame_get_pickaxe_material();

	/* Initialize an array of boxes to create a grid */
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			/* Generate a random block material */
			block_type_t block_type = digging_minigame_generate_block_material();

			/* Create the block */
			digging_minigame_block_initialize(&gridArray[i][j],
					X_COORD_INIT + (j * X_COORD_INCREMENT),
					Y_COORD_INIT + (i * Y_COORD_INCREMENT), block_type);
		}
	}

	while (!digging_minigame_is_done(gridArray)) {
		touchscreen_get_press(&touch);
		DEBUG("Touch coordinates {%d, %d}!\n", touch.x, touch.y);

		boolean block_found = FALSE;

		for (i = 0; i < 2; i++) {
			for (j = 0; j < 3; j++) {

				box.x = gridArray[i][j].x;
				box.y = gridArray[i][j].y;

				if (touchscreen_is_touch_in_box(touch, box, BOX_SIZE, BOX_SIZE)) {
					block_found = TRUE;

					/* Damage the block */
					digging_minigame_damage_block(&gridArray[i][j], damage);

					/* Update the block graphic */
					if (gridArray[i][j].health <= 0)
						gridArray[i][j].block_type = BLOCK_TYPE_DEAD;

					/* Redraw the block */
					digging_minigame_draw_block(gridArray[i][j].x,
							gridArray[i][j].y, gridArray[i][j].block_type,
							gridArray[i][j].health);

					DEBUG("Block damaged! Grid health updated:\n");
					DEBUG("[%d][%d][%d]\n", gridArray[0][0].health,
							gridArray[0][1].health, gridArray[0][2].health);
					DEBUG("[%d][%d][%d]\n\n", gridArray[1][0].health,
							gridArray[1][1].health, gridArray[1][2].health);

					break;
				}
			}
			if (block_found)
				break;
		}
	}

	DEBUG("Digging minigame finished!\n");
	return TRUE;
}

/*
 * Generates block material
 */
static int digging_minigame_generate_block_material() {
	return (rand() % (BLOCK_TYPE_NUM_TYPES - 1)) + 1;
}

/*
 * Get the pickaxe buff based on the pickaxe in the users inventory
 */
static int digging_minigame_get_pickaxe_material() {
	//TODO: Implement function
	return 1;
	//return WOOD_BUFF;
	//return STONE_BUFF;
	//return IRON_BUFF;
	//return DIAMOND_BUFF;
}

/*
 * Creates a block based on pixel coordinates
 * (x1,y1) is the top left corner of the box
 */
static void digging_minigame_block_initialize(Box *box, int x, int y, block_type_t block_type) {
	Box tempBox;

	box->x = x;
	box->y = y;
	box->health = block_type_starting_health[block_type];
	box->block_type = block_type;

	digging_minigame_draw_block(x, y, block_type, box->health);
}

/*
 * Generates the graphics for a block based on pixel coordinates
 * (x1,y1) is the top left corner of the box
 */
static void digging_minigame_draw_block(int x, int y, block_type_t block_type, int health) {
	switch (block_type) {
	case BLOCK_TYPE_WOOD:
		wood_block_generator(x, y);
		if (health <= block_type_starting_health[block_type] * 2 / 3) {
			if (health <= block_type_starting_health[block_type] / 3)
				large_crack_generator(x, y);
			else
				small_crack_generator(x, y);
		}
		break;

	case BLOCK_TYPE_STONE:
		stone_block_generator(x, y);
		if (health <= block_type_starting_health[block_type] * 2 / 3) {
			if (health <= block_type_starting_health[block_type] / 3)
				large_crack_generator(x, y);
			else
				small_crack_generator(x, y);
		}
		break;

	case BLOCK_TYPE_IRON:
		iron_block_generator(x, y);
		if (health <= block_type_starting_health[block_type] * 2 / 3) {
			if (health <= block_type_starting_health[block_type] / 3)
				large_crack_generator(x, y);
			else
				small_crack_generator(x, y);
		}
		break;

	case BLOCK_TYPE_DIAMOND:
		diamond_block_generator(x, y);
		if (health <= block_type_starting_health[block_type] * 2 / 3) {
			if (health <= block_type_starting_health[block_type] / 3)
				large_crack_generator(x, y);
			else
				small_crack_generator(x, y);
		}
		break;

	default:
		clear_block(x, y);
		break;
	}
}

/*
 * Updates health of block based on damage taken
 */
static void digging_minigame_damage_block(Box *box, int damage) {
	if (box->health <= damage) {
		clear_block(box->x, box->y);
		box->health = 0;
	} else
		box->health -= damage;
}

/*
 * Checks the combined health of the boxes to see if they have all been cleared
 */
static boolean digging_minigame_is_done(Box array[2][3]) {
	int sum = 0;
	int i, j;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			sum += array[i][j].health;
		}
	}

	if (sum == 0)
		return TRUE;
	return FALSE;
}
