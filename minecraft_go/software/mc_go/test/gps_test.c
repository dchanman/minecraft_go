/*
 *  gps_test.c
 *
 *  Created on: Jan 21, 2016
 *      Author: Johnson
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rs232.h"
#include "gps.h"

void gps_test() {
	gps_init();

	//gps_send_command(GPS_STOP_DATA_LOG);
	GGA_data *GGA_buffer = malloc(sizeof(GGA_data));
	RMC_data *RMC_buffer = malloc(sizeof(RMC_data));

	int times = 10;
	int i;
	char *data_line_buffer = malloc(GPS_DEFAULT_DATA_LINE_SIZE * sizeof(char));
	for (i = 0; i < times; i++) {
		if (!gps_retrieve_data_line(data_line_buffer, GPS_DEFAULT_DATA_LINE_SIZE)){
			printf("Buffer to testing data line is too small!\n");
			break;
		}

		//printf("%s\n", data_line_buffer);
		int isGGA = gps_get_gga_data(data_line_buffer, GGA_buffer);
		int isRMC = gps_get_rmc_data(data_line_buffer, RMC_buffer);

		if (isGGA) {
			printf("%s\n", data_line_buffer);
			printf(
					"GGA PARSED --> Time: %s Lat: %s N/S: %s Long: %s E/W: %s Satellites: %s \n",
					GGA_buffer->UTC_time, GGA_buffer->latitude, GGA_buffer->N_S,
					GGA_buffer->longitude, GGA_buffer->E_W,
					GGA_buffer->satellites);
		}

		if (isRMC) {
			printf("%s\n", data_line_buffer);
			printf(
					"RMC PARSED --> Time: %s Lat: %s N/S: %s Long: %s E/W: %s Speed: %s Date: %s \n",
					RMC_buffer->UTC_time, RMC_buffer->latitude, RMC_buffer->N_S,
					RMC_buffer->longitude, RMC_buffer->E_W,
					RMC_buffer->speed, RMC_buffer->date);
		}

	}

	convertRMCtoTime(RMC_buffer, &start_time);
	printf("Current start time -> Year: %d, Month: %d, Day: %d, Hour: %d, Minute: %d, Second: %d\n",
				start_time.year, start_time.month, start_time.day,
				start_time.hour, start_time.minute, start_time.second);


	printf("Current speed: %f\n", getSpeedFromRMC(RMC_buffer));

	/*
	 gps_send_command(GPS_DATA_DUMP_PARTIAL);
	 int buffer_size = 100;
	 char ** test_data = gps_retrive_data_dump(buffer_size);

	 int i;
	 for(i = 0; i < buffer_size; i++){
	 printf("%s \n", test_data[i]);
	 }
	 */

	/* For testing checksum
	 char array[9] = {'P','M','T','K','1','8','5',',','0'};

	 checksum(array, 9);
	 */

	free(GGA_buffer);
	free(RMC_buffer);
	free(data_line_buffer);
}

void print_test_data(char ** test_data) {
	int counter = 0;
	char curr_char;

	do {
		curr_char = test_data[counter][0];
		counter++;
		printf("%s \n", test_data[counter]);

	} while (curr_char == '$');
}
