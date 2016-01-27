/*
 * touchscreen.c
 *
 *  Created on: January 24, 2016
 *      Author: Logan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "serial.h"
#include "touchscreen.h"

#define TOUCHSCREEN	((volatile unsigned char *)(0x84000230))

static unsigned char ENABLE[] = {0x55, 0x01, 0x12};

void init_touchscreen(void){
	serial_init(TOUCHSCREEN, BAUD_RATE_9600);
	serial_put_n_char(TOUCHSCREEN, ENABLE, 3);

	if(serial_test_for_received_data(TOUCHSCREEN))
		printf("Touch Screen Initialized\n");
}

void screen_touched( void ){
	// return TRUE if any data received from 6850 connected to touchscreen
	// or FALSE otherwise
	unsigned char buffer[5] = {'\0'};

	while(buffer[0] != 0x80){
		buffer[0] = serial_get_char(TOUCHSCREEN);
	};

	serial_get_n_char(TOUCHSCREEN, buffer + 1, sizeof(buffer) - 1);
	printf("Received buffer <80> <%x> <%x> <%x> <%x>\n", buffer[1], buffer[2], buffer[3], buffer[4]);

	printf("Touch Detected!\n\n");
}

void wait_for_touch(){
	screen_touched();
}

Point get_press(void){
	Point p1;

	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	unsigned char buffer[5] = {'\0'};

	while(buffer[0] != 0x80){
		buffer[0] = serial_get_char(TOUCHSCREEN);
	};

	serial_get_n_char(TOUCHSCREEN, buffer + 1, sizeof(buffer) - 1);


	p1.x = (int)(buffer[2]) << 7;
	p1.x += (int)(buffer[1]);


	p1.y = (int)(buffer[4]) << 7;
	p1.y += (int)(buffer[3]);

	return p1;
}

Point get_release(void){
	Point p2;

	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	unsigned char buffer[5] = {'\0'};

	while(buffer[0] != 0x81){
		buffer[0] = serial_get_char(TOUCHSCREEN);
	};

	serial_get_n_char(TOUCHSCREEN, buffer + 1, sizeof(buffer) - 1);

	p2.x = (int)(buffer[2]) << 7;
	p2.x += (int)(buffer[1]);


	p2.y = (int)(buffer[4]) << 7;
	p2.y += (int)(buffer[3]);

	return p2;
}
