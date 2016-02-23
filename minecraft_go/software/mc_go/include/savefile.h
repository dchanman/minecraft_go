/*
 * savefile.h
 *
 *  Created on: Feb 11, 2016
 *      Author: derek
 */

#include "general.h"
#include "gps.h"

typedef struct savedata {
	int health;
	int creeps_defeated;
	char dest_latitude[10];
	char dest_longitude[11];
	DateTime start_time;
} savedata_t;

void savefile_init();
boolean savefile_load(savedata_t * data);
boolean savefile_save(const savedata_t data);


