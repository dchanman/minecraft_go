/*
 * sprint1_demo.c
 *
 *  Created on: Feb 2, 0216
 *      Author: derek
 */

#include "stdio.h"
#include "hw.h"
#include "test.h"
#include "gps.h"
#include "touchscreen.h"
#include "minecraft_rpc.h"
#include "hw.h"

static void gps_update_rmc(RMC_data *RMC_buffer);
static void dump_time(DateTime DateTime_buffer);

void sprint1_demo() {
	/* Initialize components */
	gps_init();
	touchscreen_init();
	minecraft_rpc_init();

	touchscreen_wait_for_touch();

	/* Get time from GPS */
	RMC_data RMC_buffer;
	DateTime DateTime_buffer;
	gps_update_rmc(&RMC_buffer);
	convert_rmc_to_datetime(&RMC_buffer, &DateTime_buffer);
	dump_time(DateTime_buffer);

	gps_start_timer(&DateTime_buffer);

	minecraft_rpc_hi();

	/* Main Loop */
	while (1) {
		Pixel box;
		box.x = 362;
		box.y = 450;

		Pixel touch;
		touchscreen_get_press(&touch);

		if (touchscreen_is_touch_in_box(touch, box, 300, 300)) {
			/* Say Hi to Minecraft Pi */
			minecraft_rpc_hi();

			/* Stop the timer */
			Time time_buffer;
			unsigned long result = gps_stop_timer(&DateTime_buffer);
			gps_convert_seconds_to_time(&time_buffer, result);

			printf("Time: %luh %dm %ds\n", time_buffer.hour, time_buffer.minute, time_buffer.second);

			/* Pass on timer to journey */
			minecraft_rpc_journey_complete((int)time_buffer.hour, time_buffer.minute, time_buffer.second, 0);
		}
	}
}






static void gps_update_rmc(RMC_data *RMC_buffer) {
	int times = 10;
	int i;
	char data_line_buffer[GPS_DEFAULT_DATA_LINE_SIZE];
	for (i = 0; i < times; i++) {
		if (!gps_retrieve_data_line(data_line_buffer,
				GPS_DEFAULT_DATA_LINE_SIZE)) {
			printf("Buffer to testing data line is too small!\n");
			break;
		}
	}
}

static void dump_time(DateTime DateTime_buffer) {
	printf(
			"Current DateTime -> Year: %d, Month: %d, Day: %d, Hour: %d, Minute: %d, Second: %d\n",
			DateTime_buffer.year, DateTime_buffer.month, DateTime_buffer.day,
			DateTime_buffer.hour, DateTime_buffer.minute,
			DateTime_buffer.second);
}
