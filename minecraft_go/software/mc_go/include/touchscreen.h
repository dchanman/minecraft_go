/*
 *  touchscreen.h
 *
 *  Created on: January 24, 2016
 *      Author: Logan
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

typedef struct {
	int x;
	int y;
} Point;

/**
 * Initialize the touchscreen controller
 */
void touchscreen_init(void);

/**
 * Test if the screen has been touched
 */
void touchscreen_screen_touched(void);

/**
 * Wait for the screen to be touched
 */
void touchscreen_wait_for_touch(void);

/**
 * Waits for a touch, then returns an X,Y coordinate
 */
Point touchscreen_get_press(void);

/**
 * Waits for a release, then returns an X,Y coordinate
 */
Point touchscreen_get_release(void);

#endif /* TOUCHSCREEN_H_ */
