/*
 * touchscreen.c
 *
 *  Created on: January 24, 2016
 *  Updated on: February 4, 2016
 *      Author: Logan
 */

#include <stdio.h>
#include "general.h"
#include "serial.h"
#include "touchscreen.h"
#include "timer.h"

#define TOUCHSCREEN	((volatile unsigned char *)(0x84000230))
#define TOUCHSCREEN_FRAME_SIZE	5
#define TOUCHSCREEN_DEBOUNCE 200000

#define TOUCHSCREEN_TIMER_ID	1

static unsigned char ENABLE[] = { 0x55, 0x01, 0x12 };

static boolean timeout_flag;

static void touchscreen_get_report_packet(unsigned char *buffer, unsigned char touchStatus);
static void touchscreen_clear_buffer();
static void touchscreen_timeout_isr();

static void touchscreen_timeout_isr() {
	timer_clear(TOUCHSCREEN_TIMER_ID);
	timeout_flag = TRUE;
}

void touchscreen_init(void) {
	serial_init(TOUCHSCREEN, BAUD_RATE_9600);
	serial_put_n_char(TOUCHSCREEN, ENABLE, 3);

	timer_init(TOUCHSCREEN_TIMER_ID, TIMER_ONESHOT, touchscreen_timeout_isr);

	if (serial_test_for_received_data(TOUCHSCREEN))
		printf("Touch Screen Initialized\n");
}

void touchscreen_screen_touched(void) {
	unsigned char buffer[TOUCHSCREEN_FRAME_SIZE] = { '\0' };

	touchscreen_get_report_packet(buffer, TOUCHSCREEN_PRESS);

	printf("Touch Detected!\n\n");
}

void touchscreen_wait_for_touch(void) {
	touchscreen_screen_touched();
}

boolean touchscreen_get_press(Pixel *pixel, const int timeout_millis) {
	Point point;

	unsigned char buffer[TOUCHSCREEN_FRAME_SIZE] = { '\0' };

	/* Set up the timer */
	timer_stop(TOUCHSCREEN_TIMER_ID);
	if (timeout_millis > 0) {
		timer_set(TOUCHSCREEN_TIMER_ID, timeout_millis);
		timer_start(TOUCHSCREEN_TIMER_ID);
	}

	timeout_flag = FALSE;
	while (timeout_flag == FALSE && serial_test_for_received_data(TOUCHSCREEN) == FALSE)
		/* Poll until an event or until we time out */;

	/* If timeout */
	if (timeout_flag == TRUE) {
		return FALSE;
	}

	touchscreen_get_report_packet(buffer, TOUCHSCREEN_PRESS);

	/* Process the high and low bytes of the coordinate values */
	point.x = (int) (buffer[2]) << 7;
	point.x += (int) (buffer[1]);

	point.y = (int) (buffer[4]) << 7;
	point.y += (int) (buffer[3]);

	touchscreen_pixel_conversion(point, pixel);

	/* Wait until the user releases the screen */
	touchscreen_clear_buffer();
	return TRUE;
}

#ifdef FALSE
/* @DEPRECATED
 * touchscreen_get_press stalls the processor until a release occurs
 */
void touchscreen_get_release(Pixel *pixel) {
	Point point;

	unsigned char buffer[TOUCHSCREEN_FRAME_SIZE] = {'\0'};

	touchscreen_get_report_packet(buffer, TOUCHSCREEN_RELEASE);

	/* Process the high and low bytes of the coordinate values */
	point.x = (int) (buffer[2]) << 7;
	point.x += (int) (buffer[1]);

	point.y = (int) (buffer[4]) << 7;
	point.y += (int) (buffer[3]);

	touchscreen_pixel_conversion(point, pixel);

	/* Debounce */
	touchscreen_clear_buffer();
}
#endif

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

void touchscreen_pixel_conversion(const Point point_in, Pixel *pixel_out) {
	/*
	 * convert the from touch report coordinates to pixel coordinates
	 */
	pixel_out->x = (int)((float)(point_in.x - REPORT_COORDINATE_MIN) *
			((float)X_MAX / (float)(REPORT_COORDINATE_MAX - REPORT_COORDINATE_MIN)));
	pixel_out->y = (int)((float)(point_in.y - REPORT_COORDINATE_MIN) *
			((float)Y_MAX / (float)(REPORT_COORDINATE_MAX - REPORT_COORDINATE_MIN)));
}

boolean touchscreen_is_touch_in_box(const Pixel touch, const Pixel box, const int box_width, const int box_height) {
    /* compares the coordinate pressed to the specified coordinate boundary */
	if(touch.x >= box.x && touch.x <= box.x + box_width)
		DEBUG("\tWithin X bounds\n");
	else
		DEBUG("\tOutside X bounds\n");

	if (touch.y >= box.y && touch.y <= box.y + box_height)
		DEBUG("\tWithin Y bounds\n");
	else
		DEBUG("\tOutside Y bounds\n");

    if((touch.x >= box.x && touch.x <= box.x + box_width) && (touch.y >= box.y && touch.y <= box.y + box_height)) {
    	printf("Touch was inside box!\n");
        return TRUE;
    } else {
        return FALSE;
    }
}

static void touchscreen_clear_buffer() {
	int i;
	unsigned char data;
	int count = 0;

	for (i = 0; i < TOUCHSCREEN_DEBOUNCE; i++)
		;

	while (serial_test_for_received_data(TOUCHSCREEN)) {
		data = serial_get_char(TOUCHSCREEN);
		//DEBUG("\t\t[%s] Cleared <0x%02x>\n", __func__, data);
		count++;

		for (i = 0; i < TOUCHSCREEN_DEBOUNCE; i++)
			;
	}

	//DEBUG("[%s]: Cleared <%d> items in the buffer\n", __func__, count);
}
