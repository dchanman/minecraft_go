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
	touchscreen_init();

	touchscreen_wait_for_touch();

	while (1) {
		Point p1 = touchscreen_get_press();
		printf("Pressed at coordinate {%d, %d}!\n", p1.x, p1.y);
		Point p2 = touchscreen_get_release();
		printf("Released at coordinate {%d, %d}!\n", p2.x, p2.y);
	}
}
