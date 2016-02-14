/*
 * digging_minigame.c
 *
 *  Created on: February 9, 2016
 *  Updated on: February 9, 2016
 *      Author: Logan
 */

#include <stdio.h>
#include "serial.h"
#include "touchscreen.h"
#include "minigames.h"
#include "Colours.h"
#include "graphics.h"
#include "block.h"

//health based on material
#define WOOD_HEALTH 3
#define STONE_HEALTH 6
#define IRON_HEALTH 10
#define DIAMOND_HEALTH 14

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
#define Y_COORD_INCREMENT 300

//length of the sides of digging minigame boxes
#define BOX_SIZE 240
#define GRID_WIDTH 720
#define GRID_HEIGHT 480

/* Static Functions */
static boolean digging_minigame_main();
static int digging_minigame_get_block_material();
static int digging_minigame_get_pickaxe_material();
static Box digging_minigame_block_initialize(int x, int y, int health);
static void digging_minigame_graphics_generator(int x, int y, int health);
static void digging_minigame_damage_block(Box *box, int damage);
static boolean digging_minigame_is_done(Box array[2][3]);


boolean digging_minigame_play() {
	printf("Digging minigame started!\n");

	/* Initialize everything */
	touchscreen_init();

	/* Start the game */
	return digging_minigame_main();
}

/*
 * Gets the health of the blocks based on the material type
 */
static boolean digging_minigame_main() {
	int i, j;
	int blockHealth = digging_minigame_get_block_material();
	int damage = digging_minigame_get_pickaxe_material();

	//initialize an array of boxes to create a grid
	Box gridArray[2][3];
	Pixel touch;
	Pixel box;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			gridArray[i][j] = digging_minigame_block_initialize(
					X_COORD_INIT + (j * X_COORD_INCREMENT),
					Y_COORD_INIT + (i * Y_COORD_INCREMENT), blockHealth);
		}
	}

	while (!digging_minigame_is_done(gridArray)) {
		touchscreen_get_press(&touch);
		printf("Touch coordinates {%d, %d}!\n", touch.x, touch.y);

		boolean blockFound = FALSE;

		for (i = 0; i < 2; i++) {
			for (j = 0; j < 3; j++) {

				box.x = gridArray[i][j].x;
				box.y = gridArray[i][j].y;

				if (touchscreen_is_touch_in_box(touch, box, BOX_SIZE, BOX_SIZE)) {
					digging_minigame_damage_block(&gridArray[i][j], damage);
					blockFound = TRUE;

					printf("Block damaged! Grid health updated:\n");
					printf("[%d][%d][%d]\n", gridArray[0][0].health,
							gridArray[0][1].health, gridArray[0][2].health);
					printf("[%d][%d][%d]\n\n", gridArray[1][0].health,
							gridArray[1][1].health, gridArray[1][2].health);

					break;
				}
			}
			if (blockFound)
				break;
		}
	}

	printf("Digging minigame finished!\n");
	return TRUE;
}

/*
 * Gets the health of the blocks based on the material type
 */
static int digging_minigame_get_block_material() {
	//TODO: Implement function
	return WOOD_HEALTH;
	//return STONE_HEALTH;
	//return IRON_HEALTH;
	//return DIAMOND_HEALTH;
}

/*
 * Get the pickaxe buff based on the pickaxe in the users inventory
 */
static int digging_minigame_get_pickaxe_material() {
	//TODO: Implement function
	return 1;
}

/*
 * Creates a block based on pixel coordinates
 * (x1,y1) is the top left corner of the box
 */
static Box digging_minigame_block_initialize(int x, int y, int health) {
	Box tempBox;

	tempBox.x = x;
	tempBox.y = y;
	tempBox.health = health;

	digging_minigame_graphics_generator(x, y, health);

	return tempBox;
}

/*
 * Generates the graphics for a block based on pixel coordinates
 * (x1,y1) is the top left corner of the box
 */
static void digging_minigame_graphics_generator(int x, int y, int health) {
	switch (health) {
	case WOOD_HEALTH:
		wood_block_generator(x, y);
		break;

	case STONE_HEALTH:
		stone_block_generator(x, y);
		break;

	case IRON_HEALTH:
		iron_block_generator(x, y);
		break;

	case DIAMOND_HEALTH:
		diamond_block_generator(x, y);
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