/*
 * creep_encounter.c
 *
 *  Created on: Feb 9, 2016
 *      Author: derek
 */

#include <stdlib.h>
#include "general.h"
#include "touchscreen.h"

/* Defines */
/* TODO: Move these into Graphics */
#define SCREEN_PIXEL_WIDTH	800
#define SCREEN_PIXEL_HEIGHT	480

#define CREEP_STARTING_HEALTH	20
#define CREEP_PIXEL_WIDTH	(SCREEN_PIXEL_WIDTH/6)
#define CREEP_PIXEL_HEIGHT	(SCREEN_PIXEL_HEIGHT/2)

/* Static Functions */
static bool creep_encounter_main(int *player_health);

bool minigame_creep_encounter(int *player_health) {
	DEBUG("Started Creep Minigame!\n");
	DEBUG("Parameters:\n\tCREEP_STARTING_HEALTH: %d\n\tCREEP_PIXEL_WIDTH: %d\n\tCREEP_PIXEL_HEIGHT: %d\n",
			CREEP_STARTING_HEALTH, CREEP_PIXEL_WIDTH, CREEP_PIXEL_HEIGHT);

	/* Initialize everything */
	touchscreen_init();

	/* Start the game */
	return creep_encounter_main(player_health);
}

static bool creep_encounter_main(int *player_health) {
	int creep_health = CREEP_STARTING_HEALTH;
	Pixel creep_location;
	Pixel touch_location;

	while (creep_health > 0 && *player_health > 0) {
		/* Update creep location */
		creep_location.x = rand() % (SCREEN_PIXEL_WIDTH - CREEP_PIXEL_WIDTH);
		creep_location.y = rand() % (SCREEN_PIXEL_HEIGHT - CREEP_PIXEL_HEIGHT);

		creep_location.x = 0;
		creep_location.y = 0;

		/* TODO: Redraw the creep */
		DEBUG("Creep at (%d, %d)\nCreep health: %d\nPlayer health: %d\n",
				creep_location.x, creep_location.y, creep_health, *player_health);

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

		/* Wait for release */
		touchscreen_get_release(&touch_location);
	}
}
