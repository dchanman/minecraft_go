/*
 * general.h
 *
 *  Created on: Jan 14, 2016
 *      Author: derek
 */

#ifndef GENERAL_H_
#define GENERAL_H_

#include <stdio.h>

#define EXIT_OK 0

typedef enum { FALSE, TRUE } boolean;

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

#define PLAYER_MAX_HEALTH	5

typedef struct Location {
	int lat_degree;
	double lat_minute;
	char lat_direction;

	int long_degree;
	double long_minute;
	char long_direction;
} Location;

#define DEBUGGING

#ifdef DEBUGGING
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

#endif /* GENERAL_H_ */
