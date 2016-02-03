/*
 * GSP.C
 *
 *  Created on: 2016-01-17
 *      Author: Johnson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "gps.h"
#include "serial.h"

#define GPS	((volatile unsigned char *)(0x84000210))

#define GGA_IDENTIFIER "$GPGGA"
#define RMC_IDENTIFIER "$GPRMC"

#define GPS_DEFAULT_DATA_RETRIEVAL_TRIES 20

#define GPS_LAT_EPSILON 0.01
#define GPS_LONG_EPSILON 0.01

#define CR_CHAR '\r'
#define LF_CHAR '\n'

/* GPS Commands */
#define GPS_SNAPSHOT_NOW "$PMTK186,1*20\r\n"

#define GPS_STOP_DATA_LOG "$PMTK185,1*23\r\n"
#define GPS_START_DATA_LOG "$PMTK185,0*22\r\n"

#define GPS_DATA_DUMP_PARTIAL "$PMTK622,1*29\r\n"
#define GPS_DATA_DUMP_END "$PMTKLOX,2*47\r\n"

/* Static Declarations */
static void gps_put_char(const unsigned char c);
static unsigned char gps_get_char();
static bool gps_get_current_rmc_data(RMC_data *buffer, int max_tries);

void gps_init() {
	serial_init(GPS, BAUD_RATE_9600);
}

static void gps_put_char(const unsigned char c) {
	serial_put_char(GPS, c);
}

static unsigned char gps_get_char() {
	return serial_get_char(GPS);
}

void gps_send_command(const char *command) {
	int counter = 0;
	char curr_char = command[counter];

	while (curr_char != '\0') {
		gps_put_char(curr_char);
		curr_char = command[++counter];
	}
}

/*
 * Retrieves 1 line that is terminated by "\r\n" from GPS device
 */
bool gps_retrieve_data_line(char *buffer, int buffer_size) {
	int char_count = 0;

	while (1) {
		if (char_count >= buffer_size - 1) {
			printf("Warning: Buffer not large enough for GPS data line; Cutting data line prematurely.");
			buffer[char_count] = '\0';
			return false;
		}

		char curr_char = gps_get_char();

		if (curr_char == CR_CHAR) {
			if (gps_get_char() == LF_CHAR)
				break;
		} else {
			buffer[char_count] = curr_char;
			char_count++;
		}
	}

	buffer[char_count] = '\0';
	return true;
}

/*
 * Retrieves the data dump of GPS data logger. Return true if all data from dump
 * is placed in buffer.
 *
 * buffer - 2D array where each index will hold a data line
 */
bool gps_retrieve_data_dump(char *buffer[GPS_DEFAULT_DATA_LINE_SIZE],
		int buffer_size) {
	int i;

	for (i = 0; i < buffer_size; i++) {
		gps_retrieve_data_line(buffer[i], GPS_DEFAULT_DATA_LINE_SIZE);

		if (strstr(buffer[i], GPS_DATA_DUMP_END) != NULL)
			break;

		if (i == buffer_size - 1) {
			printf("Warning: Data dump reached max buffer size!\n");
			return false;
		}
	}

	return true;
}

bool gps_get_gga_data(char *data_line, GGA_data *buffer) {
	const char delimiter[2] = ",";

	// to prevent the original data line from being modified
	char data_line_copy[strlen(data_line)];
	strcpy(data_line_copy, data_line);

	char *token = strtok(data_line_copy, delimiter);

	if (strcmp(token, GGA_IDENTIFIER) != 0) {
		//printf("Line is not in GGA format!\n");
		return false;
	}

	int count = 0;
	while (token != NULL) {
		switch (count) {
		case 1:
			snprintf(buffer->UTC_time, 11, token);
			break;
		case 2:
			snprintf(buffer->latitude, 10, token);
			break;
		case 3:
			snprintf(buffer->N_S, 2, token);
			break;
		case 4:
			snprintf(buffer->longitude, 11, token);
			break;
		case 5:
			snprintf(buffer->E_W, 2, token);
			break;
		case 7:
			snprintf(buffer->satellites, 3, token);
			break;
		default:
			break; // leave the other fields for now
		}

		//printf("Current token: %s \n", token);
		token = strtok(NULL, delimiter);

		count++;
	}

	return true;
}

bool gps_get_rmc_data(char *data_line, RMC_data *buffer) {
	const char delimiter[2] = ",";

	// to prevent the original data line from being modified
	char data_line_copy[strlen(data_line)];
	strcpy(data_line_copy, data_line);

	char * token = strtok(data_line_copy, delimiter);

	if (strcmp(token, RMC_IDENTIFIER) != 0) {
		//printf("Line is not in GGA format!\n");
		return false;
	}

	int count = 0;
	while (token != NULL) {
		switch (count) {
		case 1:
			snprintf(buffer->UTC_time, 11, token);
			break;
		case 3:
			snprintf(buffer->latitude, 10, token);
			break;
		case 4:
			snprintf(buffer->N_S, 2, token);
			break;
		case 5:
			snprintf(buffer->longitude, 11, token);
			break;
		case 6:
			snprintf(buffer->E_W, 2, token);
			break;
		case 7:
			snprintf(buffer->speed, 5, token);
			break;
		case 9:
			snprintf(buffer->date, 7, token);
			break;
		default:
			break; // leave the out other fields
		}

		//printf("Current token: %s \n", token);
		token = strtok(NULL, delimiter);

		count++;
	}

	return true;
}

/*
 *  Get the most up to date RMC data. Return true if succeed before max_tries.
 *
 *  max_tries param is intend to prevent program from staling when GPS is not
 *  working and a value of 20 should be enough unless we are in the middle of
 *  a large data dump.
 */
static bool gps_get_current_rmc_data(RMC_data *buffer, int max_tries) {
	char data_line_buffer[GPS_DEFAULT_DATA_LINE_SIZE];

	int num_tries = 0;
	do {
		num_tries++;
		gps_retrieve_data_line(data_line_buffer, GPS_DEFAULT_DATA_LINE_SIZE);
	} while (!gps_get_rmc_data(data_line_buffer, buffer) && num_tries < max_tries);

	return num_tries >= max_tries ? false : true;
}

//---------------------------Timer Functions------------------------------//

void convert_rmc_to_datetime(RMC_data *RMC_data, DateTime *buffer) {
	char RMC_year[3] = { 0 };
	strncpy(RMC_year, RMC_data->date + 4, 2);
	buffer->year = atoi(RMC_year);

	char RMC_month[3] = { 0 };
	strncpy(RMC_month, RMC_data->date + 2, 2);
	buffer->month = atoi(RMC_month);

	char RMC_day[3] = { 0 };
	strncpy(RMC_day, RMC_data->date, 2);
	buffer->day = atoi(RMC_day);

	char RMC_hour[3] = { 0 };
	strncpy(RMC_hour, RMC_data->UTC_time, 2);
	buffer->hour = atoi(RMC_hour);

	char RMC_minute[3] = { 0 };
	strncpy(RMC_minute, RMC_data->UTC_time + 2, 2);
	buffer->minute = atoi(RMC_minute);

	char RMC_second[3] = { 0 };
	strncpy(RMC_second, RMC_data->UTC_time + 4, 2);
	buffer->second = atoi(RMC_second);
}

/*
 *  Return elapsed time in seconds from start till finish
 *
 *  For simplicity, assume each year is 365 days, month is 30 days for now.
 */
unsigned long gps_get_elapsed_seconds(DateTime *start, DateTime *finish) {
	unsigned long start_in_seconds;
	unsigned long finish_in_seconds;

	start_in_seconds = start->year * 31536000 +
					   start->month * 2592000 +
					   start->day * 86400 +
					   start->hour * 3600 +
					   start->minute * 60 +
					   start->second;

	finish_in_seconds = finish->year * 31536000 +
					    finish->month * 2592000 +
					    finish->day * 86400 +
					    finish->hour * 3600 +
					    finish->minute * 60 +
					    finish->second;

	return finish_in_seconds - start_in_seconds;
}

void gps_convert_seconds_to_time(Time *buffer, unsigned long seconds) {
	unsigned long left_over;

	buffer->hour = seconds / 3600;
	left_over = seconds % 3600;
	buffer->minute = (int) left_over / 60;
	buffer->second = (int) left_over % 60;
}

void gps_start_timer(DateTime *start_time) {
	RMC_data RMC_buffer;

	if (!gps_get_current_rmc_data(&RMC_buffer, GPS_DEFAULT_DATA_RETRIEVAL_TRIES))
		printf("Error: Unable to retrieve RMC data in %d tries.\n", GPS_DEFAULT_DATA_RETRIEVAL_TRIES);
	else
		convert_rmc_to_datetime(&RMC_buffer, start_time);
}

unsigned long gps_stop_timer(DateTime *start_time) {
	RMC_data RMC_buffer;
	DateTime finish_time;

	if (!gps_get_current_rmc_data(&RMC_buffer, GPS_DEFAULT_DATA_RETRIEVAL_TRIES))
		printf("Error: Unable to retrieve RMC data in %d tries.\n", GPS_DEFAULT_DATA_RETRIEVAL_TRIES);
	else
		convert_rmc_to_datetime(&RMC_buffer, &finish_time);

	unsigned long result = gps_get_elapsed_seconds(start_time, &finish_time);

	return result;
}
//--------------------------End Timer Functions---------------------------//

//--------------------------Speed Function---------------------------//

/*
 * Return the speed in km/h (converted from knots)
 *
 * Note: GPS can claim speed of up to 0.08km/h even
 * when not moving due to device limitations
 */
float gps_get_speed_from_rmc(RMC_data *RMC_data) {
	float speed_knots = atof(RMC_data->speed);

	return speed_knots * 1.852; // 1 knots = 1.852 km/h
}

//--------------------------End Speed Functions---------------------------//

//--------------------------Location Functions---------------------------//

void gps_convert_rmc_to_location(RMC_data *RMC_data, Location *buffer) {
	char RMC_LatDegree[3] = { 0 };
	strncpy(RMC_LatDegree, RMC_data->latitude, 2);
	buffer->lat_degree = atoi(RMC_LatDegree);

	char RMC_LatMinute[8] = { 0 };
	strncpy(RMC_LatMinute, RMC_data->latitude + 2, 7);
	buffer->lat_minute = atof(RMC_LatMinute);

	buffer->lat_direction = RMC_data->N_S[0];

	char RMC_LongDegree[4] = { 0 };
	strncpy(RMC_LongDegree, RMC_data->longitude, 3);
	buffer->long_degree = atoi(RMC_LongDegree);

	char RMC_LongMinute[8] = { 0 };
	strncpy(RMC_LongMinute, RMC_data->longitude + 3, 7);
	buffer->long_minute = atof(RMC_LongMinute);

	buffer->long_direction = RMC_data->E_W[0];
}

/* Compares two location and if they are close enough, return true.
 * Note: algorithm might not work if the the 2 locations are right on
 * 		the Equator or Prime Meridian
 */
bool gps_has_arrived_at_destination(Location *current, Location *destination) {
	// this will work for North America, re-implement part later if needed
	if (current->lat_direction != destination->lat_direction
			|| current->long_direction != destination->long_direction)
		return false;

	double currLatInMinutes = current->lat_degree * 60 + current->lat_minute;
	double destLatInMinutes = destination->lat_degree * 60
			+ destination->lat_minute;

	double currLongInMinutes = current->long_degree * 60 + current->long_minute;
	double destLongInMinutes = destination->long_degree * 60
			+ destination->long_minute;

	if (abs(currLatInMinutes - destLatInMinutes) < GPS_LAT_EPSILON
			&& abs(currLongInMinutes - destLongInMinutes) < GPS_LONG_EPSILON)
		return true;
	else
		return false;
}

//--------------------------End Location Functions---------------------------//

void gps_checksum(char *string, int size) {
	int i;
	char result = string[0];
	for (i = 1; i < size; i++) {
		printf("XORing: %c %d ", string[i], string[i]);
		result ^= string[i];
	}

	printf("Checksum: %x \n", result);
}
