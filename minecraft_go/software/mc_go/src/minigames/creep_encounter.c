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

/* Defines */
#define CREEP_STARTING_HEALTH	20
#define CREEP_PIXEL_WIDTH	(GRAPHICS_PIXEL_WIDTH/6)
#define CREEP_PIXEL_HEIGHT	(GRAPHICS_PIXEL_HEIGHT/2)

/* Static Functions */
static bool creep_encounter_main(int *player_health);
static void creep_encounter_draw_creep(Pixel creep_location);
static void creep_encounter_erase_creep(Pixel creep_location);
static void creep_encounter_draw_creep_helper(Pixel creep_location, int colour);

bool minigame_creep_encounter(int *player_health) {
	DEBUG("Started Creep Minigame!\n");
	DEBUG("Parameters:\n\tCREEP_STARTING_HEALTH: %d\n\tCREEP_PIXEL_WIDTH: %d\n\tCREEP_PIXEL_HEIGHT: %d\n",
			CREEP_STARTING_HEALTH, CREEP_PIXEL_WIDTH, CREEP_PIXEL_HEIGHT);

	/* Initialize everything */
	touchscreen_init();
	graphics_clear_screen();

	/* Start the game */
	return creep_encounter_main(player_health);
}

static bool creep_encounter_main(int *player_health) {
	int creep_health = CREEP_STARTING_HEALTH;
	Pixel creep_location;
	Pixel touch_location;

	while (creep_health > 0 && *player_health > 0) {
		/* Update creep location */
		creep_location.x = rand() % (GRAPHICS_PIXEL_WIDTH - CREEP_PIXEL_WIDTH);
		creep_location.y = rand() % (GRAPHICS_PIXEL_HEIGHT - CREEP_PIXEL_HEIGHT);

		DEBUG("Creep at (%d, %d)\nCreep health: %d\nPlayer health: %d\n",
				creep_location.x, creep_location.y, creep_health, *player_health);

		creep_encounter_draw_creep(creep_location);

		/* Wait for touch */
		touchscreen_get_press(&touch_location);
		DEBUG("Touched (%d, %d)\n", touch_location.x, touch_location.y);

		/* Update health */
		if (touchscreen_is_touch_in_box(touch_location, creep_location, CREEP_PIXEL_WIDTH, CREEP_PIXEL_HEIGHT)) {
			DEBUG("Hit the creep!\n");
			creep_health--;
		} else {
			DEBUG("Missed the creep!\n");
			(*player_health)--;
		}

		/* Erase previous creep */
		creep_encounter_erase_creep(creep_location);
	}

	/* Determine whether the player won or lost */
	if (creep_health <= 0) {
		DEBUG("You won!\n");
		return true;
	} else {
		DEBUG("You lost!\n");
		return false;
	}
}

static void creep_encounter_draw_creep(Pixel creep_location) {
	creep_encounter_draw_creep_helper(creep_location, RED);
}

static void creep_encounter_erase_creep(Pixel creep_location) {
	creep_encounter_draw_creep_helper(creep_location, GRAPHICS_BACKGROUND_COLOUR);
}

static void creep_encounter_draw_creep_helper(Pixel creep_location, int colour) {
	graphics_draw_rectangle_filled(creep_location.x, creep_location.y, CREEP_PIXEL_WIDTH, CREEP_PIXEL_HEIGHT, colour);
}
