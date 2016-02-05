/*
 *  touchscreen.h
 *
 *  Created on: January 24, 2016
 *  Updated on: February 4, 2016
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
 * Waits for a touch, then returns an X,Y coordinate
 */
Pixel touchscreen_get_press(void);

/**
 * Waits for a release, then returns an X,Y coordinate
 */
Pixel touchscreen_get_release(void);

/**
 * Converts touch report coordinates to pixel coordinates
 */
Pixel touchscreen_pixel_conversion(Point p);

/*
 *	Checks if the point pressed is inside a specified coordinate boundary
 *	(x1,y1) is the top left corner of the box
 *	(x2,y2) is the bottom right corner of the box
 */
int touchscreen_is_touch_in_box(int x1, int y1, int x2, int y2);

#endif /* TOUCHSCREEN_H_ */
