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
#include "creeper.h"
#include "heart.h"

void touchscreen_test() {
	touchscreen_init();

	//clear screen
	clear_block(0, 0);
	clear_block(0, 240);
	clear_block(240, 0);
	clear_block(240, 240);
	clear_block(480, 0);
	clear_block(480, 240);
	clear_block(720, 0);
	clear_block(720, 240);

	// block generator test
	wood_block_generator(0, 0);
	stone_block_generator(242, 0);
	iron_block_generator(0, 241);
	diamond_block_generator(242, 241);

	// creeper generator test
	creeper_generator(500, 250, 100);

	// heart generator test
	heart_draw(500, 10, 50);
	heart_draw(500, 60, 100);

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
    	touchscreen_get_press(&touch, -1);

    	boolean result = touchscreen_is_touch_in_box(touch, box, 300, 300);
    	printf("Touch %s in box\n", (result ? "is" : "is not"));
    }

    printf("Touch screen test is complete!\n");
}

void touchscreen_test_timeout() {
	printf("[%s]\n", __func__);
	touchscreen_init();
	while (1) {
		Pixel touch;
		boolean result = touchscreen_get_press(&touch, 3000);

		if (!result)
			printf("Timed out!\n");
		else
			printf("Pressed (%d, %d)\n", touch.x, touch.y);
	}
}
