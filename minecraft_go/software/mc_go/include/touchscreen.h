/*
 *  touchscreen.h
 *
 *  Created on: January 24, 2016
 *  Updated on: February 4, 2016
 *      Author: Logan
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#include "general.h"

//touch screen
#define TOUCHSCREEN_PRESS 0x80
#define TOUCHSCREEN_RELEASE 0X81

//touch screen pixel resolution
#define X_MAX 800
#define Y_MAX 480

//touch report coordinate boundaries
#define REPORT_COORDINATE_MAX 4096
#define REPORT_COORDINATE_MIN 0

//type declaration for touch report coordinates
typedef struct {
	int x;
	int y;
} Point;

//type declaration for pixel coordinates
typedef struct {
	int x;
	int y;
} Pixel;

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
 * Waits for a touch, then returns an X,Y coordinate.
 *
 * @param pixel - where the touch output is stored
 * @param timeout_millis - timeout value in milliseconds. Set to -1 for no timeout
 * @return TRUE if touch, FALSE if timeout
 */
boolean touchscreen_get_press(Pixel *pixel, const int timeout_millis);

/**
 * Waits for a release, then returns an X,Y coordinate
 *
 * @DEPRECATED
 */
/* void touchscreen_get_release(Pixel *pixel); */

/**
 * Converts touch report coordinates to pixel coordinates
 */
void touchscreen_pixel_conversion(const Point point_in, Pixel *pixel);

/*
 *	Checks if the point pressed is inside a specified coordinate boundary
 *	@param touch - the Pixel coordinates of a touch
 *	@param box - the Pixel coordinate of the top left corner of the box
 *	@param box_width - the width of the box
 *	@param box_height - the height of the box
 */
boolean touchscreen_is_touch_in_box(const Pixel touch, const Pixel box, const int box_width, const int box_height);

#endif /* TOUCHSCREEN_H_ */
