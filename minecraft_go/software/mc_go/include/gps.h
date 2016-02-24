/*
 * GSP.h
 *
 *  Created on: 2016-01-17
 *      Author: Johnson
 */
#include "general.h"

#ifndef GPS_H_
#define GPS_H_

#define GPS_DEFAULT_DATA_LINE_SIZE 300

typedef struct GGA_data {
	char UTC_time[11];
	char latitude[10];
	char N_S[2];
	char longitude[11];
	char E_W[2];
	char satellites[3];
} GGA_data;

typedef struct RMC_data {
	char UTC_time[11]; // hhmmss.sss
	char latitude[10]; // ddmm.mmmm
	char N_S[2];
	char longitude[11]; // dddmm.mmmm
	char E_W[2];
	char speed[5]; // knots
	char date[7]; //ddmmyy
} RMC_data;

typedef struct Location {
	int lat_degree;
	double lat_minute;
	char lat_direction;

	int long_degree;
	double long_minute;
	char long_direction;
} Location;

/**
 *
 */
void gps_init();

/**
 *
 */
void gps_send_command(const char *command);

/**
 *
 */
boolean gps_retrieve_data_line(char *buffer, int buffer_size);

/**
 *
 */
boolean gps_retrieve_data_dump(char **buffer, int buffer_size);

/**
 *
 */
boolean gps_get_gga_data(char *data_line, GGA_data *buffer);

/**
 *
 */
boolean gps_get_rmc_data(char *data_line, RMC_data *buffer);

/**
 *
 */
void convert_rmc_to_datetime(RMC_data *RMC_data, DateTime *buffer);

/**
 *
 */
unsigned long gps_get_elapsed_seconds(DateTime *start, DateTime *finish);

/**
 *
 */
void gps_convert_seconds_to_time(Time *buffer, unsigned long seconds);

/**
 *
 */
void gps_start_timer(DateTime *start_time);

/**
 *
 */
unsigned long gps_stop_timer(DateTime *start_time);

/**
 *
 */
float gps_get_speed_from_rmc(RMC_data *RMC_data);

/**
 *
 */
void gps_convert_rmc_to_location(RMC_data *RMC_data, Location *buffer);

double gps_get_distance(Location *, Location *);


/**
 * Compares two location and if they are close enough, return true.
 * Note: algorithm might not work if the the 2 locations are right on
 * the Equator or Prime Meridian
 */
boolean gps_has_arrived_at_destination(Location *current, Location *destination);

/**
 *
 */
void gps_checksum(char *string, int size);

#endif /* GPS_H_ */
