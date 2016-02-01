/*
 *  touchscreen.h
 *
 *  Created on: January 24, 2016
 *      Author: Logan
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

//touch screen
#define TOUCHSCREEN_PRESS 0x80
#define TOUCHSCREEN_RELEASE 0X81

//touch screen pixel resolution
#define X_MAX 1024
#define Y_MAX 600

//touch report coordinate boundaries
#define REPORT_COORDINATE_MAX 4096
#define REPORT_COORDINATE_MIN 0

typedef struct {
	int x;
	int y;
} Point;

/**
 * Initialize the touch screen controller
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

/**
 * Reads the serial port to get the touch report packet
 */
void touchscreen_get_report_packet(unsigned char *buffer, unsigned char touchStatus);

/**
 * Converts touch report coordinates to pixel coordinates
 */
Point touchscreen_pixel_conversion(Point p);

#endif /* TOUCHSCREEN_H_ */
