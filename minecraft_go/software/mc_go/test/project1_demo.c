/*
 * project1_demo.c
 *
 *  Created on: Feb 23, 2016
 *      Author: derek
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hw.h"
#include "gps.h"
#include "savefile.h"
#include "minigames.h"
#include "minecraft_rpc.h"

void project1_demo_initialize_savefile() {
	savedata_t data;

	savefile_init();

	/* Initialize data */
	data.creeps_defeated = 0;
	data.health = 10;
	data.start_time.year = 0;
	data.start_time.month = 0;
	data.start_time.day = 0;
	data.start_time.hour = 0;
	data.start_time.minute = 0;
	data.start_time.second = 0;
	memset(data.dest_latitude, '\0', sizeof(data.dest_latitude));
	memset(data.dest_longitude, '\0', sizeof(data.dest_longitude));

	/* Commit to SD Card */
	savefile_save(data);
}

void project1_demo_main() {
	savedata_t data;
	char sw;
	DateTime end_time;
	Time elapsed_time;
	unsigned long elapsed_time_seconds;
	boolean result;

	/* Initialize everything */
	savefile_init();
	minecraft_rpc_init();
	gps_init();

	/* Load from savefile */
	savefile_init();
	savefile_load(&data);

	/* Demo loop */
	while (1) {
		/* Hardware controls */

		sw = hw_switches_get();
		switch (sw) {
		case 0x00:
			/* Do nothing */
			break;

		case 0x01:
			/* Get coordinates from Minecraft Server */
			DEBUG("Getting coordinates from Minecraft Server\n");
			minecraft_rpc_hi();
			result = minecraft_rpc_receive_coordinates(data.dest_latitude,
					sizeof(data.dest_latitude), data.dest_longitude,
					sizeof(data.dest_longitude));
			if (result == FALSE)
				printf("Error receiving coordinates from Minecraft server\n");

			printf("Savedata loaded:"
					"\n\thealth: <%d>"
					"\n\tcreeps defeated: <%d>"
					"\n\tlatitude: <%s>"
					"\n\tlongitude: <%s>"
					"\n\tstart_time.year: <%d>"
					"\n\tstart_time.month: <%d>"
					"\n\tstart_time.day: <%d>"
					"\n\tstart_time.hour: <%d>"
					"\n\tstart_time.minute: <%d>"
					"\n\tstart_time.second: <%d>"
					"\n", data.health, data.creeps_defeated, data.dest_latitude,
					data.dest_longitude, data.start_time.year,
					data.start_time.month, data.start_time.day,
					data.start_time.hour, data.start_time.minute,
					data.start_time.second);

			/* TODO: Start journey */
			//gps_start_timer(&data.start_time);
			break;

		case 0x02:

			/* Encounter creepers */
			DEBUG("Playing creeper minigame\n");
			result = minigame_creeper_encounter(&data.health);

			if (result == FALSE) {
				printf("You died!\n");
				/* TODO: do stuff because player sucks */
			} else {
				data.creeps_defeated++;
			}
			break;

		case 0x04:

			/* Try to get closer to destination */
			/* TODO: Fake this by changing the destination */

			break;

		case 0x08:

			/* Arrive at destination */
			/* TODO: detect arrival */

			/* Play digging minigame */
			minigame_digging();
			break;

		case 0x10:
			/* Report to the Minecraft Server */
			DEBUG("Home now! Reporting to server\n");
			minecraft_rpc_hi();

			/* TODO: Calculate elapsed time */
			//gps_stop_timer(&end_time);
			end_time.year = 0;
			end_time.month = 1;
			end_time.day = 1;
			end_time.hour = 1;
			end_time.minute = 1;
			end_time.second = 1;
			elapsed_time_seconds = gps_get_elapsed_seconds(&data.start_time,
					&end_time);
			gps_convert_seconds_to_time(&elapsed_time, elapsed_time_seconds);

			minecraft_rpc_journey_complete(elapsed_time.hour,
					elapsed_time.minute, elapsed_time.second,
					data.creeps_defeated);
			break;

		default:
			DEBUG("No demo option for 0x%02x\n", sw);
			break;
		}

		/* TODO: Display journey menu */


		/* Save data every time */
		savefile_save(data);

		/* Wait for a toggle */
		while (hw_switches_get() == sw)
			;
	}

}