/*
 * touchscreen.c
 *
 *  Created on: January 24, 2016
 *  Updated on: February 4, 2016
 *      Author: Logan
 */

#include <stdio.h>
#include "serial.h"
#include "touchscreen.h"

#define TOUCHSCREEN	((volatile unsigned char *)(0x84000230))
#define TOUCHSCREEN_FRAME_SIZE	5

static unsigned char ENABLE[] = { 0x55, 0x01, 0x12 };

static void touchscreen_get_report_packet(unsigned char *buffer, unsigned char touchStatus);

void touchscreen_init(void) {
	serial_init(TOUCHSCREEN, BAUD_RATE_9600);
	serial_put_n_char(TOUCHSCREEN, ENABLE, 3);

	if (serial_test_for_received_data(TOUCHSCREEN))
		printf("Touch Screen Initialized\n");
}

void touchscreen_screen_touched(void) {
	unsigned char buffer[5] = { '\0' };

	touchscreen_get_report_packet(buffer, TOUCHSCREEN_PRESS);

	printf("Touch Detected!\n\n");
}

void touchscreen_wait_for_touch(void) {
	touchscreen_screen_touched();
}

Pixel touchscreen_get_press(void) {
	Point point;

	unsigned char buffer[TOUCHSCREEN_FRAME_SIZE] = { '\0' };

	touchscreen_get_report_packet(buffer, TOUCHSCREEN_PRESS);

	/* Process the high and low bytes of the coordinate values */
	point.x = (int) (buffer[2]) << 7;
	point.x += (int) (buffer[1]);

	point.y = (int) (buffer[4]) << 7;
	point.y += (int) (buffer[3]);

	Pixel pixel = touchscreen_pixel_conversion(point);

	return pixel;
}

Pixel touchscreen_get_release(void) {
	Point point;

	unsigned char buffer[TOUCHSCREEN_FRAME_SIZE] = {'\0'};

	touchscreen_get_report_packet(buffer, TOUCHSCREEN_RELEASE);

	/* Process the high and low bytes of the coordinate values */
	point.x = (int) (buffer[2]) << 7;
	point.x += (int) (buffer[1]);

	point.y = (int) (buffer[4]) << 7;
	point.y += (int) (buffer[3]);

	Pixel pixel = touchscreen_pixel_conversion(point);

	return pixel;
}

/**
 * Reads the serial port to get the touch report packet
 */
static void touchscreen_get_report_packet(unsigned char *buffer, unsigned char touchStatus) {
	/**
	 * wait for a pen up command then return the X,Y coord of the point
	 * calibrated correctly so that it maps to a pixel on screen
	*/
	while (buffer[0] != touchStatus) {
		buffer[0] = serial_get_char(TOUCHSCREEN);
	};

	serial_get_n_char(TOUCHSCREEN, buffer + 1, sizeof(buffer));
	//printf("Received buffer <0x%02x> <0x%02x> <0x%02x> <0x%02x> <0x%02x>\n",
			//buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
}

Pixel touchscreen_pixel_conversion(Point p){
	/*
	 * convert the from touch report coordinates to pixel coordinates
	 */
	Pixel pixel;

	pixel.x = (int)((float)(p.x - REPORT_COORDINATE_MIN) *
			((float)X_MAX / (float)(REPORT_COORDINATE_MAX - REPORT_COORDINATE_MIN)));
	pixel.y = (int)((float)(p.y - REPORT_COORDINATE_MIN) *
			((float)Y_MAX / (float)(REPORT_COORDINATE_MAX - REPORT_COORDINATE_MIN)));

	return pixel;
}

int touchscreen_is_touch_in_box(int x1, int y1, int x2, int y2) {
	Pixel pixel = touchscreen_get_press();

    //compares the coordinate pressed to the specified coordinate boundary
    if((pixel.x >= x1 && pixel.x <= x2) && (pixel.y <= y1 && pixel.y >= y2)){
    	printf("Touch was inside box!\n");
        return 1;
    }
    else
        return 0;
}
