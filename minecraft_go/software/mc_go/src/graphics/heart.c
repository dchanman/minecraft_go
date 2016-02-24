/*
 * creeper.c
 *
 *  Created on: February 12, 2016
 *  Updated on: February 12, 2016
 *      Author: Logan
 */

#include <stdio.h>
#include "Colours.h"
#include "graphics.h"

//colours used for heart
#define COLOUR_1 BLACK
#define COLOUR_2 PINK
#define COLOUR_3 LIGHT_CORAL
#define COLOUR_4 RED
#define COLOUR_5 FIREBRICK
#define COLOUR_6 -1
#define COLOUR_7 GRAY

//pixel width of heart bitmap
#define HEART_PIXEL_WIDTH 13
#define HEART_PIXEL_HEIGHT	11


/* Static Functions */
static void heart_generator(int x, int y, int pixelSize);


void heart_draw(int x, int y, int width) {
	int pixelSize = width / HEART_PIXEL_WIDTH;

	heart_generator(x, y, pixelSize);
}

void heart_draw_empty(int x, int y, int width) {
	int pixelSize = width / HEART_PIXEL_WIDTH;

	heart_empty_generator(x, y, pixelSize);
}

/*
 * generates a heart
 * x - top left x coordinate
 * y - top left y coordinate
 * pixelSize - width and length of each pixel box
 */
static void heart_generator(int x, int y, int pixelSize) {
	int i, j;
	int tempX = x;

	int fullHeartColours[HEART_PIXEL_HEIGHT][HEART_PIXEL_WIDTH] = {
								{COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_1, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_1, COLOUR_1, COLOUR_6, COLOUR_6}, //row 1
								{COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_1, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_1, COLOUR_6}, //row 2
								{COLOUR_1, COLOUR_4, COLOUR_2, COLOUR_3, COLOUR_4, COLOUR_4, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_1}, //row 3
								{COLOUR_1, COLOUR_4, COLOUR_3, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_1}, //row 4
								{COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1}, //row 5
								{COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1, COLOUR_6}, //row 6
								{COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1, COLOUR_6, COLOUR_6}, //row 7
								{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6}, //row 8
								{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6}, //row 9
								{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6}, //row 10
								{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6}}; //row 11

	//implements graphics based on colors from color matrix heartColours
	for (i = 0; i < HEART_PIXEL_HEIGHT; i++) {
		for (j = 0; j < HEART_PIXEL_WIDTH; j++) {
			//COLOUR_6
			if(fullHeartColours[i][j] != COLOUR_6) {
				graphics_draw_rectangle_filled(x, y, pixelSize, pixelSize, fullHeartColours[i][j]);
			}
			x += pixelSize;
		}
		x = tempX;
		y += pixelSize;
	}
}

void heart_erase(int x, int y, int width) {
	int pixelSize = width / HEART_PIXEL_WIDTH;
	graphics_draw_rectangle_filled(x, y, pixelSize * HEART_PIXEL_WIDTH,
			pixelSize * HEART_PIXEL_HEIGHT, GRAPHICS_BACKGROUND_COLOUR);
}

void heart_empty_generator(int x, int y, int pixelSize) {
	int i, j;
	int tempX = x;

	int emptyHeartColours[HEART_PIXEL_HEIGHT][HEART_PIXEL_WIDTH] = {
								{COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_1, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_1, COLOUR_1, COLOUR_6, COLOUR_6}, //row 1
								{COLOUR_6, COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1, COLOUR_6, COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1, COLOUR_6}, //row 2
								{COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1}, //row 3
								{COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1}, //row 4
								{COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1}, //row 5
								{COLOUR_6, COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1, COLOUR_6}, //row 6
								{COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1, COLOUR_6, COLOUR_6}, //row 7
								{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6}, //row 8
								{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_7, COLOUR_7, COLOUR_7, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6}, //row 9
								{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_7, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6}, //row 10
								{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6}}; //row 11

	//implements graphics based on colors from color matrix heartColours
	for (i = 0; i < HEART_PIXEL_HEIGHT; i++) {
		for (j = 0; j < HEART_PIXEL_WIDTH; j++) {
			//COLOUR_6
			if(emptyHeartColours[i][j] != COLOUR_6) {
				graphics_draw_rectangle_filled(x, y, pixelSize, pixelSize, emptyHeartColours[i][j]);
			}
			x += pixelSize;
		}
		x = tempX;
		y += pixelSize;
	}
}
