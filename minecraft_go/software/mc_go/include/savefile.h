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
	Location destination;
	DateTime start_time;
	boolean journey_complete;
} savedata_t;

void savefile_init();
boolean savefile_load(savedata_t * data);
boolean savefile_save(const savedata_t data);


