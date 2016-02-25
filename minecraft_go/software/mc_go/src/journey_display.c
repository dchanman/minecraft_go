/*
 *  journey_display.c
 *
 *  Created on: 2016-02-23
 *      Author: Johnson
 */

#include <stdint.h>
#include <stdio.h>
#include "journey_display.h"
#include "graphics.h"
#include "gps.h"
#include "colours.h"



void displayElapsedTime(Time *elapsedTime, int start_x_coord, int y_coord){
	char buffer[100];

	sprintf(buffer, "Elapsed Time: %dhr %dmin %dsec", elapsedTime->hour, elapsedTime->minute, elapsedTime->second);

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont4(start_x_coord + i*12, y_coord, RED, GRAPHICS_BACKGROUND_COLOUR , buffer[i], FALSE);
		i++;
	}
}

void displayDestDistance(double dist_km,  int start_x_coord, int y_coord){
	char buffer[100];

	sprintf(buffer, "Destination Distance: %.2fkm", dist_km);

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont4(start_x_coord + i*12, y_coord, RED, GRAPHICS_BACKGROUND_COLOUR , buffer[i], FALSE);
		i++;
	}
}

void displaySpeed(float speed_km_h,  int start_x_coord, int y_coord){
	char buffer[100];

	sprintf(buffer, "Current Speed: %.2fkm/h", speed_km_h);

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont4(start_x_coord + i*12, y_coord, RED, GRAPHICS_BACKGROUND_COLOUR , buffer[i], FALSE);
		i++;
	}
}

