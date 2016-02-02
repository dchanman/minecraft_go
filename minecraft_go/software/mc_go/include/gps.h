/*
 * GSP.h
 *
 *  Created on: 2016-01-17
 *      Author: Johnson
 */
#include "general.h"

#ifndef GSP_H_
#define GSP_H_

#define GGA_IDENTIFIER "$GPGGA"
#define RMC_IDENTIFIER "$GPRMC"

#define GPS_DEFAULT_DATA_LINE_SIZE 300
#define GPS_DEFAULT_DATA_RETRIEVAL_TRIES 20

#define GPS_LAT_EPSILON 0.01
#define GPS_LONG_EPSILON 0.01

// GPS Commands
#define GPS_SNAPSHOT_NOW "$PMTK186,1*20\r\n"

#define GPS_STOP_DATA_LOG "$PMTK185,1*23\r\n"
#define GPS_START_DATA_LOG "$PMTK185,0*22\r\n"

#define GPS_DATA_DUMP_PARTIAL "$PMTK622,1*29\r\n"
#define GPS_DATA_DUMP_END "$PMTKLOX,2*47\r\n"

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

typedef struct DateTime {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
} DateTime;

typedef struct Time {
	unsigned long hour;
	int minute;
	int second;
} Time;

typedef struct Location {
	int Lat_degree;
	double Lat_minute;
	char Lat_direction;

	int Long_degree;
	double Long_minute;
	char Long_direction;
} Location;


//DateTime start_time;

bool gps_retrieve_data_line(char *, int);
bool gps_retrieve_data_dump(char **, int);
void gps_send_command(const char *);
void gps_init();
bool gps_get_gga_data(char *, GGA_data *);
bool gps_get_rmc_data(char *, RMC_data *);
void convertRMCtoDateTime(RMC_data *, DateTime *);
unsigned long getElapsedInSeconds(DateTime *, DateTime *);
float getSpeedFromRMC(RMC_data *);
void convertRMCtoLocation(RMC_data *, Location *);


void gps_checksum(char *, int);

#endif /* GSP_H_ */
