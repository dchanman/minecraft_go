/*
 * main_controller.c
 *
 *  Created on: Feb 25, 2016
 *      Author: derek
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "general.h"
#include "hw.h"
#include "gps.h"
#include "savefile.h"
#include "minigames.h"
#include "minecraft_rpc.h"
#include "graphics.h"
#include "journey_display.h"
#include "touchscreen.h"

#define DISTANCE_TO_DESTINATION_THRESHOLD	5

typedef enum {
	STATE_JOURNEY = 0,
	STATE_RECEIVE_COORDINATES,
	STATE_CREEPER_MINIGAME,
	STATE_ARRIVED_AT_DESTINATION,
	STATE_REPORT_RESULTS
} state_t;

static state_t main_controller_state_journey(savedata_t *data);
static state_t main_controller_state_receive_coordinates(savedata_t *data);
static state_t main_controller_state_creeper_minigame(savedata_t *data);
static state_t main_controller_state_arrived_at_destination(savedata_t *data);
static state_t main_controller_state_report_results(savedata_t *data);
static state_t main_controller_journey_menu_buttons(const savedata_t data);

void main_controller_run() {
	savedata_t data;
	state_t current_state = STATE_JOURNEY;
	state_t prev_state = current_state;

	/* Initialize all components */
	savefile_init();
	minecraft_rpc_init();
	gps_init();
	graphics_clear_screen();

	/* Load data from SD Card */
	savefile_init();
	savefile_load(&data);

	/* Main loop */
	while (1) {
		switch (current_state) {
		case STATE_JOURNEY:
			current_state = main_controller_state_journey(&data);
			break;
		case STATE_RECEIVE_COORDINATES:
			current_state = main_controller_state_receive_coordinates(&data);
			break;
		case STATE_CREEPER_MINIGAME:
			current_state = main_controller_state_creeper_minigame(&data);
			break;
		case STATE_ARRIVED_AT_DESTINATION:
			current_state = main_controller_state_arrived_at_destination(&data);
			break;
		case STATE_REPORT_RESULTS:
			current_state = main_controller_state_report_results(&data);
			break;
		}

		/* If we're changing states, do some cleanup */
		if (current_state != prev_state) {
			graphics_clear_screen();
			savefile_save(data);
		}

		prev_state = current_state;
	}
}

/**
 * This state does the following:
 * * display journey menu.
 * * update GPS data
 * * listens for user input on the switches
 */
static state_t main_controller_state_journey(savedata_t *data) {
	Time current_time;
	double distance_to_destination;
	float speed;

	/* Update GPS data */
	// TODO: get gps location
	long journey_time = gps_stop_timer(&data->start_time);
	gps_convert_seconds_to_time(&current_time, journey_time);

	/* Check if we've arrived at our destination */
	if (!data->journey_complete && distance_to_destination < DISTANCE_TO_DESTINATION_THRESHOLD)
		return STATE_ARRIVED_AT_DESTINATION;

	/* Update journey display */
	displayBackground();
	displayMenu(&current_time, distance_to_destination, speed, data->creeps_defeated);

	/* Poll for user input */
	return main_controller_journey_menu_buttons(*data);
}

/**
 * This state gets coordinates from the Minecraft Server and resets the journey data
 */
static state_t main_controller_state_receive_coordinates(savedata_t *data) {
	boolean result;
	Location new_destination;

	minecraft_rpc_hi();
	result = minecraft_rpc_receive_coordinates(&new_destination);
	if (result == FALSE)
		return STATE_JOURNEY;

	/* Set up our new journey data */
	data->destination = new_destination;
	data->health = PLAYER_MAX_HEALTH;
	data->journey_complete = FALSE;
	gps_start_timer(&data->start_time);

	return STATE_JOURNEY;
}

static state_t main_controller_state_creeper_minigame(savedata_t *data) {
	boolean result;

	result = minigame_creeper_encounter(&data->health);
	if (result)
		data->creeps_defeated++;
	else
		data->health = PLAYER_MAX_HEALTH;

	return STATE_JOURNEY;
}

/**
 * This state starts the digging minigame and completes the journey
 */
static state_t main_controller_state_arrived_at_destination(savedata_t *data) {
	/* Play the digging minigame */
	minigame_digging();

	/* We've arrived! */
	data->journey_complete = TRUE;

	return STATE_JOURNEY;
}

/**
 * This state uploads the journey data to the Minecraft Pi server
 */
static state_t main_controller_state_report_results(savedata_t *data) {
	boolean result;
	Time journey_elapsed_time;
	long journey_elapsed_seconds;
	Pixel touch;

	/* Update journey data */
	journey_elapsed_seconds = gps_stop_timer(&data->start_time);
	gps_convert_seconds_to_time(&journey_elapsed_time, journey_elapsed_seconds);

	minecraft_rpc_hi();
	result = minecraft_rpc_journey_complete(journey_elapsed_time.hour, journey_elapsed_time.minute, journey_elapsed_time.second, data->creeps_defeated);
	if (!result)
		return STATE_JOURNEY;

	/* Display a congrats screen */
	graphics_clear_screen();

	/* Wait for touch and return */
	touchscreen_get_press(&touch, -1);

	/* Ready for next adventure! */
	return STATE_RECEIVE_COORDINATES;
}

/**
 * This is just a janky helper function. Needs to be refactored later.
 */
static state_t main_controller_journey_menu_buttons(const savedata_t data) {
	Pixel touch_location;
	boolean touch_result;

	static Pixel creeper_minigame_hitbox;
	creeper_minigame_hitbox.x = 600;
	creeper_minigame_hitbox.y = 200;

	static Pixel connect_hitbox;
	connect_hitbox.x = 600;
	connect_hitbox.y = 300;

	static int button_width = 100;
	static int button_height = 50;

	touch_result = touchscreen_get_press(&touch_location, 800);

	if (touch_result) {
		graphics_draw_rectangle_filled(creeper_minigame_hitbox.x, creeper_minigame_hitbox.y, button_width, button_height, MAGENTA);
		graphics_draw_rectangle_filled(connect_hitbox.x, connect_hitbox.y, button_width, button_height, TEAL);

		if (touchscreen_is_touch_in_box(touch_location, creeper_minigame_hitbox, button_width, button_height)) {
			return STATE_CREEPER_MINIGAME;
		} else if (touchscreen_is_touch_in_box(touch_location, connect_hitbox, button_width, button_height)) {
			if (data.journey_complete)
				return STATE_REPORT_RESULTS;
			else
				return STATE_RECEIVE_COORDINATES;
		}
	}

	return STATE_JOURNEY;
}
