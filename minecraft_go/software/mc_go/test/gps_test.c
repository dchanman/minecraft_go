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
#include <unistd.h>
#include <general.h>
#include "rs232.h"
#include "gps.h"

void gps_test() {
	/*
	int lat_degree;
	double lat_minute;
	char lat_direction; N +

	int long_degree;
	double long_minute;
	char long_direction; E +
	*/

	// dist b/w A and B should be 0.549KM
	Location A = {38, 0.898556 * 60, 'N', 77, 0.037852 * 60, 'W'};
	Location B = {38, 0.897147 * 60, 'N', 77, 0.043934 * 60, 'W'};

	Location C = {38, 54.2, 'N', 77, 0.31, 'W'};
	Location D = {38, 55, 'N', 77, 0.42, 'W'};
	Location E = {38, 56, 'N', 77, 0.68, 'W'};
	Location destination = {38, 57, 'N', 77, 0.74, 'W'};

	Location positions[] = {A, B, C, D, E, destination};

	int pos_count = 0;
	boolean hasArrive = FALSE;
	while (!hasArrive){
		hasArrive = gps_has_arrived_at_destination(&(positions[pos_count]), &destination);

		if (!hasArrive){
			double distKM = gps_get_distance(&(positions[pos_count]), &destination);
			printf("Distance from destination is: %lf km\n", distKM);
			usleep(3000000);
			pos_count++;
		} else {
			printf("You have arrived at the destionation.\n");
			break;
		}
	}


	/*
	gps_init();

	//gps_send_command(GPS_STOP_DATA_LOG);
	GGA_data GGA_buffer;
	RMC_data RMC_buffer;

	int times = 10;
	int i;
	char data_line_buffer[GPS_DEFAULT_DATA_LINE_SIZE];
	for (i = 0; i < times; i++) {
		if (!gps_retrieve_data_line(data_line_buffer, GPS_DEFAULT_DATA_LINE_SIZE)){
			printf("Buffer to testing data line is too small!\n");
			break;
		}

		//printf("%s\n", data_line_buffer);
		int isGGA = gps_get_gga_data(data_line_buffer, &GGA_buffer);
		int isRMC = gps_get_rmc_data(data_line_buffer, &RMC_buffer);

		if (isGGA) {
			printf("%s\n", data_line_buffer);
			printf(
					"GGA PARSED --> Time: %s Lat: %s N/S: %s Long: %s E/W: %s Satellites: %s \n",
					GGA_buffer.UTC_time, GGA_buffer.latitude, GGA_buffer.N_S,
					GGA_buffer.longitude, GGA_buffer.E_W,
					GGA_buffer.satellites);
		}

		if (isRMC) {
			printf("%s\n", data_line_buffer);
			printf(
					"RMC PARSED --> Time: %s Lat: %s N/S: %s Long: %s E/W: %s Speed: %s Date: %s \n",
					RMC_buffer.UTC_time, RMC_buffer.latitude, RMC_buffer.N_S,
					RMC_buffer.longitude, RMC_buffer.E_W,
					RMC_buffer.speed, RMC_buffer.date);
		}
	}

	Location location_buffer;

	gps_convert_rmc_to_location(&RMC_buffer, &location_buffer);
	printf("Current Location -> Lat Degree: %d, Lat Minute: %lf, Lat Direction: %c, "
							   "Long Degree: %d, Long_Minute: %lf, Long_Direction: %c\n",
				location_buffer.lat_degree, location_buffer.lat_minute, location_buffer.lat_direction,
				location_buffer.long_degree, location_buffer.long_minute, location_buffer.long_direction);

	if (!gps_has_arrived_at_destination(&location_buffer, &location_buffer))
		printf("Error: hasArriveAtDestination() is not working!\n");

	printf("Current speed: %f\n", gps_get_speed_from_rmc(&RMC_buffer));



	// testing DateTime struc and convertRMCtoDateTime()
	DateTime DateTime_buffer;

	convert_rmc_to_datetime(&RMC_buffer, &DateTime_buffer);
	printf("Current DateTime -> Year: %d, Month: %d, Day: %d, Hour: %d, Minute: %d, Second: %d\n",
				DateTime_buffer.year, DateTime_buffer.month, DateTime_buffer.day,
				DateTime_buffer.hour, DateTime_buffer.minute, DateTime_buffer.second);

	// testing timer
	DateTime testStartTime = {16, 2, 2, 0, 0, 0};

	unsigned long testElapsedTime = gps_stop_timer(&testStartTime);

	Time testTime;

	gps_convert_seconds_to_time(&testTime, testElapsedTime);
	printf("Elapsed Time . Hour: %d, Minute: %d, Second: %d \n", testTime.hour,
																  testTime.minute,
																  testTime.second);

	*/





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
