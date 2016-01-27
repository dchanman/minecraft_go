/*
 *  touchscreen_test.c
 *
 *  Created on: January 24, 2016
 *      Author: Logan
 */

#include <stdint.h>
#include <stdio.h>
#include "touchscreen.h"

void touchscreen_test() {
	init_touchscreen();

	wait_for_touch();

	int pressCount = 0;
	int releaseCount = 0;

	while(pressCount < 5){
		Point p1 = get_press();
		printf("Pressed at coordinate {%d, %d}!\n", p1.x, p1.y);
		pressCount++;
	}

	while(releaseCount < 5){
		Point p2 = get_release();
		printf("Released at coordinate {%d, %d}!\n", p2.x, p2.y);
		releaseCount++;
	}
}
