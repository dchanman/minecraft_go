/*
 * creep_encounter.c
 *
 *  Created on: Feb 9, 2016
 *      Author: derek
 */

#include <stdlib.h>
#include "general.h"
#include "touchscreen.h"
#include "graphics.h"
#include "creeper.h"
#include "heart.h"
#include "journey_display.h"

/* Defines */
#define CREEPER_STARTING_HEALTH	20
#define CREEPER_PIXEL_WIDTH	(GRAPHICS_PIXEL_WIDTH/6)
/* This height is a hack. The 24/14 ratio comes from looking at how the creeper is drawn in creeper.c */
#define CREEPER_PIXEL_HEIGHT	(CREEPER_PIXEL_WIDTH*24/14)

/* Let's put the hearts at the bottom 1/8th of the screen */
#define CREEPER_HEART_Y_VAL	(GRAPHICS_PIXEL_HEIGHT*7/8)
#define CREEPER_HEART_MAX_NUM	15
#define CREEPER_HEART_WIDTH	(GRAPHICS_PIXEL_WIDTH/CREEPER_HEART_MAX_NUM)

#define CREEPER_MAX_DODGE_COUNT	2

/* Static Functions */
static boolean creeper_encounter_main(int *player_health);
static void creeper_encounter_damage_player(int * player_health);
static void creeper_encounter_draw_creeper(Pixel creeper_location);
static void creeper_encounter_erase_creeper(Pixel creeper_location);
static void creeper_encounter_draw_creep_helper(Pixel creeper_location, int colour);
static void creeper_encounter_erase_hearts();
static void creeper_encounter_draw_hearts(int num_hearts, int num_empty_hearts);

boolean minigame_creeper_encounter(int *player_health) {
	DEBUG("Started Creeper Minigame!\n");
	DEBUG("Parameters:\n\tCREEPER_STARTING_HEALTH: %d\n\tCREEPER_PIXEL_WIDTH: %d\n\tCREEPER_PIXEL_HEIGHT: %d\n",
			CREEPER_STARTING_HEALTH, CREEPER_PIXEL_WIDTH, CREEPER_PIXEL_HEIGHT);

	/* Initialize everything */
	touchscreen_init();
	graphics_clear_screen();

	/* Start the game */
	printf("Starting game\n");
	return creeper_encounter_main(player_health);
}

static boolean creeper_encounter_main(int *player_health) {
	boolean touched;
	int dodgecount;
	int creeper_health = CREEPER_STARTING_HEALTH;
	Pixel creeper_location;
	Pixel touch_location;

	displayTextBox("Touch to start!", WHITE, BLACK, BLACK);
	touchscreen_get_press(&touch_location, 1500);
	graphics_clear_screen();

	dodgecount = 0;
	while (creeper_health > 0 && *player_health > 0) {
		/* Update creep location */
		creeper_location.x = rand() % (GRAPHICS_PIXEL_WIDTH - CREEPER_PIXEL_WIDTH);
		creeper_location.y = rand() % (GRAPHICS_PIXEL_HEIGHT - CREEPER_PIXEL_HEIGHT);

		DEBUG("Creeper at (%d, %d)\nCreeper health: %d\nPlayer health: %d\n",
				creeper_location.x, creeper_location.y, creeper_health, *player_health);

		/* Draw the creeper */
		creeper_encounter_draw_creeper(creeper_location);

		/* Draw hearts (hearts displayed in front of creeper) */
		creeper_encounter_draw_hearts(*player_health, PLAYER_MAX_HEALTH);

		/* Wait for touch */
		int time = rand()%400 + 200;
		touched = touchscreen_get_press(&touch_location, time);
		dodgecount++;

		if (!touched) {
			/* Timeout */
			DEBUG("Took too long!\n");
		} else {
			/* Registered touch */
			DEBUG("Touched (%d, %d)\n", touch_location.x, touch_location.y);



			if (touchscreen_is_touch_in_box(touch_location, creeper_location, CREEPER_PIXEL_WIDTH, CREEPER_PIXEL_HEIGHT)) {
				DEBUG("Hit the creep!\n");
				creeper_health--;
				dodgecount = 0;
			} else {
				DEBUG("Missed the creep!\n");
				//creeper_encounter_damage_player(player_health);
			}
		}

		if (dodgecount > CREEPER_MAX_DODGE_COUNT) {
			creeper_encounter_damage_player(player_health);
			dodgecount = 0;
		}

		/* Erase previous creep */
		creeper_encounter_erase_creeper(creeper_location);
	}

	/* Draw hearts */
	creeper_encounter_draw_hearts(*player_health, PLAYER_MAX_HEALTH);

	/* Determine whether the player won or lost */
	if (creeper_health <= 0) {
		DEBUG("You won!\n");
		displayWin();
		usleep(2000000);
		return TRUE;
	} else {
		DEBUG("You lost!\n");
		displayLose();
		usleep(2000000);
		return FALSE;
	}
}

static void creeper_encounter_damage_player(int * player_health) {
	//graphics_fill_screen(RED);
	//usleep(400000);
	//graphics_clear_screen();
	(*player_health)--;
}

static void creeper_encounter_erase_hearts() {
	int i;

	for (i = 0; i < CREEPER_HEART_MAX_NUM; i++)
		heart_erase(CREEPER_HEART_WIDTH*i, CREEPER_HEART_Y_VAL, CREEPER_HEART_WIDTH);
}

static void creeper_encounter_draw_hearts(int num_hearts, int num_empty_hearts) {
	int i;
	int j;

	for (i = 0; i < num_hearts && i < CREEPER_HEART_MAX_NUM; i++)
		heart_draw(CREEPER_HEART_WIDTH*i, CREEPER_HEART_Y_VAL, CREEPER_HEART_WIDTH);

	for (j = 0; (i+j) < num_empty_hearts && (i+j) < CREEPER_HEART_MAX_NUM; j++)
		heart_draw_empty(CREEPER_HEART_WIDTH*(i+j), CREEPER_HEART_Y_VAL, CREEPER_HEART_WIDTH);
}

static void creeper_encounter_draw_creeper(Pixel creeper_location) {
	// For debugging, uncomment this line. You'll see a red hitbox */
	//creeper_encounter_draw_creep_helper(creeper_location, RED);

	creeper_generator(creeper_location.x, creeper_location.y, CREEPER_PIXEL_WIDTH);
}

static void creeper_encounter_erase_creeper(Pixel creeper_location) {
	creeper_encounter_draw_creep_helper(creeper_location, GRAPHICS_BACKGROUND_COLOUR);
}

static void creeper_encounter_draw_creep_helper(Pixel creeper_location, int colour) {
	graphics_draw_rectangle_filled(creeper_location.x, creeper_location.y, CREEPER_PIXEL_WIDTH, CREEPER_PIXEL_HEIGHT, colour);
}
