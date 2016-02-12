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
#include "block.h"

void touchscreen_test() {
	touchscreen_init();

	clear_block(100, 0);
	wood_block_generator(100, 0);

	clear_block(340, 0);
	stone_block_generator(340, 0);

	clear_block(100, 240);
	iron_block_generator(100, 240);

	clear_block(340, 240);
	diamond_block_generator(340, 240);

	touchscreen_wait_for_touch();

	/*
    Pixel p1 = touchscreen_get_press();
    printf("Pressed at coordinate {%d, %d}!\n", p1.x, p1.y);
    Pixel p2 = touchscreen_get_release();
    printf("Released at coordinate {%d, %d}!\n\n", p2.x, p2.y);
	*/

    //300x300 block in the middle of touch screen
    while(1){
    	Pixel box;
    	box.x = 362;
    	box.y = 450;

    	Pixel touch;
    	touchscreen_get_press(&touch);

    	bool result = touchscreen_is_touch_in_box(touch, box, 300, 300);
    	printf("Touch %s in box\n", (result ? "is" : "is not"));
    }

    printf("Touch screen test is complete!\n");
}
