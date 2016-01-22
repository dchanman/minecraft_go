/*
 *  gps_test.c
 *
 *  Created on: Jan 21, 2016
 *      Author: Johnson
 */

#include <stdint.h>
#include <stdio.h>
#include "rs232.h"
#include "gps.h"

void gps_test() {
	gps_init();

	//gps_send_command(GPS_STOP_DATA_LOG);
	struct gga_data *GGA_holder = malloc(sizeof(struct gga_data));

	int times = 10;
	int i;
	char * result;
	for (i = 0; i < times; i++) {
		result = gps_retrive_data_line(1000);
		printf("%s\n", result);
		int isGGA = gps_get_gga_data(result, GGA_holder);

		if (isGGA)
			printf(
					"Time: %s Lat: %s N/S: %s Long: %s E/W: %s Satellites: %s \n",
					GGA_holder->UTC_time, GGA_holder->latitude, GGA_holder->N_S,
					GGA_holder->longitude, GGA_holder->E_W,
					GGA_holder->satellites);
	}

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
