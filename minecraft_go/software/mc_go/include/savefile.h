/*
 * savefile.h
 *
 *  Created on: Feb 11, 2016
 *      Author: derek
 */

#include "general.h"

typedef struct savedata {
	int health;
	int creeps_defeated;
} savedata_t;

void savefile_init();
boolean savefile_load(savedata_t * data);
boolean savefile_save(const savedata_t data);


