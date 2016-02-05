/*
 *  touchscreen_test.c
 *
 *  Created on: January 24, 2016
 *  Updated on: February 4, 2016
 *      Author: Logan
 */

#include <stdint.h>
#include <stdio.h>
#include "touchscreen.h"

void touchscreen_test() {
	touchscreen_init();

	touchscreen_wait_for_touch();

	/*
    Pixel p1 = touchscreen_get_press();
    printf("Pressed at coordinate {%d, %d}!\n", p1.x, p1.y);
    Pixel p2 = touchscreen_get_release();
    printf("Released at coordinate {%d, %d}!\n\n", p2.x, p2.y);
	*/

    //300x300 block in the middle of touch screen
    while(1){
    	int i = touchscreen_is_touch_in_box(362, 450, 662, 150);
    }

    printf("Touch screen test is complete!\n");
}
