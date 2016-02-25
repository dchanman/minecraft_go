/*
 * block.c
 *
 *  Created on: February 10, 2016
 *  Updated on: February 10, 2016
 *      Author: Logan
 */

#include <stdio.h>
#include "Colours.h"
#include "graphics.h"
#include "block.h"

//blank space for crack pixels
#define BLANK -1

//colours used for wood block
#define WOOD_COLOUR_1 SADDLE_BROWN
#define WOOD_COLOUR_2 BLACK

//colours for grass block
#define GRASS_COLOUR_1 LIGHT_GREEN
#define GRASS_COLOUR_2 LIME_GREEN


//colours for soil blocks
#define SOIL_COLOUR_1 SADDLE_BROWN
#define SOIL_COLOUR_2 SANDY_BROWN

//colours used for stone block
#define STONE_COLOUR_1 LIGHT_GRAY
#define STONE_COLOUR_2 GRAY
#define STONE_COLOUR_3 DARK_GRAY

//colours used for iron block
#define IRON_COLOUR_1 GRAY
#define IRON_COLOUR_2 WHITE
#define IRON_COLOUR_3 TAN
#define IRON_COLOUR_4 SANDY_BROWN

//colours used for diamond block
#define DIAMOND_COLOUR_1 GRAY
#define DIAMOND_COLOUR_2 WHITE
#define DIAMOND_COLOUR_3 DEEP_SKY_BLUE
#define DIAMOND_COLOUR_4 CYAN

//set size of each individual "pixel" in block graphics
#define PIXEL_SIZE 15
#define BLOCK_PIXEL_SIZE 16

void clear_block(int x, int y) {
	graphics_draw_rectangle_filled(x, y, 240, 240, GRAPHICS_BACKGROUND_COLOUR);
}

void small_crack_generator(int x, int y){
	int i, j;
	int tempX = x;

	int smallCrackMatrix[BLOCK_PIXEL_SIZE][BLOCK_PIXEL_SIZE] = {
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 1
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 2
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 3							{COLOUR_1, COLOUR_4, COLOUR_3, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_1}, //row 4
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 4							{COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1, COLOUR_6}, //row 6
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 5							{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6}, //row 8
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLACK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK}, //row 6							{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6}, //row 10
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK}, //row 7
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 8
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 9
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 10
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 11
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 12
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 13
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 14
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 15
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}}; //row 16

	//implements graphics based on colors from color matrix heartColours
	for (i = 0; i < BLOCK_PIXEL_SIZE; i++) {
		for (j = 0; j < BLOCK_PIXEL_SIZE; j++) {
			//BLANK
			if(smallCrackMatrix[i][j] != BLANK) {
				graphics_draw_rectangle_filled(x, y, PIXEL_SIZE, PIXEL_SIZE, smallCrackMatrix[i][j]);
			}
			x += PIXEL_SIZE;
		}
		x = tempX;
		y += PIXEL_SIZE;
	}
}

void large_crack_generator(int x, int y) {
	int i, j;
	int tempX = x;

	int largeCrackMatrix[BLOCK_PIXEL_SIZE][BLOCK_PIXEL_SIZE] = {
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 1
							{BLANK, BLANK, BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 2
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 3							{COLOUR_1, COLOUR_4, COLOUR_3, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_1}, //row 4
							{BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK}, //row 4							{COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1, COLOUR_6}, //row 6
							{BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLACK, BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLACK, BLACK, BLANK}, //row 5							{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_4, COLOUR_5, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6}, //row 8
							{BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLACK, BLANK, BLANK, BLACK, BLANK, BLANK, BLACK, BLANK, BLANK, BLACK}, //row 6							{COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_1, COLOUR_4, COLOUR_1, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6, COLOUR_6}, //row 10
							{BLANK, BLANK, BLANK, BLANK, BLACK, BLACK, BLACK, BLANK, BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK}, //row 7
							{BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLACK, BLANK, BLACK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK}, //row 8
							{BLANK, BLANK, BLACK, BLANK, BLANK, BLACK, BLANK, BLANK, BLACK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK}, //row 9
							{BLANK, BLANK, BLACK, BLANK, BLACK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK}, //row 10
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 11
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLACK, BLACK, BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK}, //row 12
							{BLANK, BLACK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}, //row 13
							{BLANK, BLANK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK, BLANK, BLACK, BLACK, BLACK, BLANK, BLANK, BLANK, BLANK}, //row 14
							{BLANK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK, BLACK, BLANK, BLANK, BLANK}, //row 15
							{BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK}}; //row 16

	//implements graphics based on colors from color matrix heartColours
	for (i = 0; i < BLOCK_PIXEL_SIZE; i++) {
		for (j = 0; j < BLOCK_PIXEL_SIZE; j++) {
			//BLANK
			if(largeCrackMatrix[i][j] != BLANK) {
				graphics_draw_rectangle_filled(x, y, PIXEL_SIZE, PIXEL_SIZE, largeCrackMatrix[i][j]);
			}
			x += PIXEL_SIZE;
		}
		x = tempX;
		y += PIXEL_SIZE;
	}
}

/**************************************************************
 * Wood Block
 **************************************************************/
void wood_block_generator(int x, int y) {
    //column 1
    graphics_draw_rectangle_filled(x + 0, y + 0, PIXEL_SIZE, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 0, y + 45, PIXEL_SIZE, 105, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 0, y + 150, PIXEL_SIZE, 75, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 0, y + 225, PIXEL_SIZE, 15, WOOD_COLOUR_1);

    //column 2
    graphics_draw_rectangle_filled(x + 15, y + 0, PIXEL_SIZE, 45, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 45, PIXEL_SIZE, 30, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 15, y + 75, PIXEL_SIZE, 165, WOOD_COLOUR_1);

    //column 3
    graphics_draw_rectangle_filled(x + 30, y + 0, PIXEL_SIZE, 105, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 105, PIXEL_SIZE, 90, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 195, PIXEL_SIZE, 45, WOOD_COLOUR_1);

    //column 4
    graphics_draw_rectangle_filled(x + 45, y + 0, PIXEL_SIZE, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 45, y + 15, PIXEL_SIZE, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 60, PIXEL_SIZE, 180, WOOD_COLOUR_1);

    //column 5
    graphics_draw_rectangle_filled(x + 60, y + 0, PIXEL_SIZE, 30, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 30, PIXEL_SIZE, 210, WOOD_COLOUR_1);

    //column 6
    graphics_draw_rectangle_filled(x + 75, y + 0, PIXEL_SIZE, 105, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 75, y + 105, PIXEL_SIZE, 30, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 135, PIXEL_SIZE, 105, WOOD_COLOUR_1);

    //column 7
    graphics_draw_rectangle_filled(x + 90, y + 0, PIXEL_SIZE, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 15, PIXEL_SIZE, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 60, PIXEL_SIZE, 75, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 135, PIXEL_SIZE, 90, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 225, PIXEL_SIZE, 15, WOOD_COLOUR_1);

    //column 8
    graphics_draw_rectangle_filled(x + 105, y + 0, PIXEL_SIZE, 15, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 15, PIXEL_SIZE, 75, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 90, PIXEL_SIZE, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 135, PIXEL_SIZE, 75, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 210, PIXEL_SIZE, 30, WOOD_COLOUR_2);

    //column 9
    graphics_draw_rectangle_filled(x + 120, y + 0, PIXEL_SIZE, 150, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 150, PIXEL_SIZE, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 195, PIXEL_SIZE, 45, WOOD_COLOUR_1);

    //column 10
    graphics_draw_rectangle_filled(x + 135, y + 0, PIXEL_SIZE, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 15, PIXEL_SIZE, 135, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 150, PIXEL_SIZE, 90, WOOD_COLOUR_1);

    //column 11
    graphics_draw_rectangle_filled(x + 150, y + 0, PIXEL_SIZE, 240, WOOD_COLOUR_1);

    //column 12
    graphics_draw_rectangle_filled(x + 165, y + 0, PIXEL_SIZE, 90, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 165, y + 90, PIXEL_SIZE, 150, WOOD_COLOUR_2);

    //column 13
    graphics_draw_rectangle_filled(x + 180, y + 0, PIXEL_SIZE, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 15, PIXEL_SIZE, 90, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 105, PIXEL_SIZE, 135, WOOD_COLOUR_1);

    //column 14
    graphics_draw_rectangle_filled(x + 195, y + 0, PIXEL_SIZE, 240, WOOD_COLOUR_1);

    //column 15
    graphics_draw_rectangle_filled(x + 210, y + 0, PIXEL_SIZE, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 15, PIXEL_SIZE, 180, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 195, PIXEL_SIZE, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 210, PIXEL_SIZE, 15, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 225, PIXEL_SIZE, 15, WOOD_COLOUR_1);

    //column 16
    graphics_draw_rectangle_filled(x + 225, y + 0, PIXEL_SIZE, 195, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 225, y + 195, PIXEL_SIZE, 15, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 210, PIXEL_SIZE, 30, WOOD_COLOUR_1);
}

/**************************************************************
 * GRASS BLOCK
 **************************************************************/
void grass_block_generator(int x, int y) {
    //column 1
    graphics_draw_rectangle_filled(x + 0, y + 0, PIXEL_SIZE, 45, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 0, y + 45, PIXEL_SIZE, 105, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 0, y + 150, PIXEL_SIZE, 75, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 0, y + 225, PIXEL_SIZE, 15, GRASS_COLOUR_1);

    //column 2
    graphics_draw_rectangle_filled(x + 15, y + 0, PIXEL_SIZE, 45, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 45, PIXEL_SIZE, 30, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 15, y + 75, PIXEL_SIZE, 165, GRASS_COLOUR_1);

    //column 3
    graphics_draw_rectangle_filled(x + 30, y + 0, PIXEL_SIZE, 105, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 105, PIXEL_SIZE, 90, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 195, PIXEL_SIZE, 45, GRASS_COLOUR_1);

    //column 4
    graphics_draw_rectangle_filled(x + 45, y + 0, PIXEL_SIZE, 15, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 45, y + 15, PIXEL_SIZE, 45, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 60, PIXEL_SIZE, 180, GRASS_COLOUR_1);

    //column 5
    graphics_draw_rectangle_filled(x + 60, y + 0, PIXEL_SIZE, 30, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 30, PIXEL_SIZE, 210, GRASS_COLOUR_1);

    //column 6
    graphics_draw_rectangle_filled(x + 75, y + 0, PIXEL_SIZE, 105, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 75, y + 105, PIXEL_SIZE, 30, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 135, PIXEL_SIZE, 105, GRASS_COLOUR_1);

    //column 7
    graphics_draw_rectangle_filled(x + 90, y + 0, PIXEL_SIZE, 15, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 15, PIXEL_SIZE, 45, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 60, PIXEL_SIZE, 75, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 135, PIXEL_SIZE, 90, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 225, PIXEL_SIZE, 15, GRASS_COLOUR_1);

    //column 8
    graphics_draw_rectangle_filled(x + 105, y + 0, PIXEL_SIZE, 15, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 15, PIXEL_SIZE, 75, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 90, PIXEL_SIZE, 45, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 135, PIXEL_SIZE, 75, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 210, PIXEL_SIZE, 30, GRASS_COLOUR_2);

    //column 9
    graphics_draw_rectangle_filled(x + 120, y + 0, PIXEL_SIZE, 150, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 150, PIXEL_SIZE, 45, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 195, PIXEL_SIZE, 45, GRASS_COLOUR_1);

    //column 10
    graphics_draw_rectangle_filled(x + 135, y + 0, PIXEL_SIZE, 15, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 15, PIXEL_SIZE, 135, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 150, PIXEL_SIZE, 90, GRASS_COLOUR_1);

    //column 11
    graphics_draw_rectangle_filled(x + 150, y + 0, PIXEL_SIZE, 240, GRASS_COLOUR_1);

    //column 12
    graphics_draw_rectangle_filled(x + 165, y + 0, PIXEL_SIZE, 90, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 165, y + 90, PIXEL_SIZE, 150, GRASS_COLOUR_2);

    //column 13
    graphics_draw_rectangle_filled(x + 180, y + 0, PIXEL_SIZE, 15, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 15, PIXEL_SIZE, 90, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 105, PIXEL_SIZE, 135, GRASS_COLOUR_1);

    //column 14
    graphics_draw_rectangle_filled(x + 195, y + 0, PIXEL_SIZE, 240, GRASS_COLOUR_1);

    //column 15
    graphics_draw_rectangle_filled(x + 210, y + 0, PIXEL_SIZE, 15, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 15, PIXEL_SIZE, 180, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 195, PIXEL_SIZE, 15, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 210, PIXEL_SIZE, 15, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 225, PIXEL_SIZE, 15, GRASS_COLOUR_1);

    //column 16
    graphics_draw_rectangle_filled(x + 225, y + 0, PIXEL_SIZE, 195, GRASS_COLOUR_1);
    graphics_draw_rectangle_filled(x + 225, y + 195, PIXEL_SIZE, 15, GRASS_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 210, PIXEL_SIZE, 30, GRASS_COLOUR_1);
}

/**************************************************************
 * SOIL BLOCK
 **************************************************************/
void soil_block_generator(int x, int y) {
    //column 1
    graphics_draw_rectangle_filled(x + 0, y + 0, PIXEL_SIZE, 45, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 0, y + 45, PIXEL_SIZE, 105, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 0, y + 150, PIXEL_SIZE, 75, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 0, y + 225, PIXEL_SIZE, 15, SOIL_COLOUR_1);

    //column 2
    graphics_draw_rectangle_filled(x + 15, y + 0, PIXEL_SIZE, 45, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 45, PIXEL_SIZE, 30, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 15, y + 75, PIXEL_SIZE, 165, SOIL_COLOUR_1);

    //column 3
    graphics_draw_rectangle_filled(x + 30, y + 0, PIXEL_SIZE, 105, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 105, PIXEL_SIZE, 90, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 195, PIXEL_SIZE, 45, SOIL_COLOUR_1);

    //column 4
    graphics_draw_rectangle_filled(x + 45, y + 0, PIXEL_SIZE, 15, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 45, y + 15, PIXEL_SIZE, 45, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 60, PIXEL_SIZE, 180, SOIL_COLOUR_1);

    //column 5
    graphics_draw_rectangle_filled(x + 60, y + 0, PIXEL_SIZE, 30, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 30, PIXEL_SIZE, 210, SOIL_COLOUR_1);

    //column 6
    graphics_draw_rectangle_filled(x + 75, y + 0, PIXEL_SIZE, 105, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 75, y + 105, PIXEL_SIZE, 30, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 135, PIXEL_SIZE, 105, SOIL_COLOUR_1);

    //column 7
    graphics_draw_rectangle_filled(x + 90, y + 0, PIXEL_SIZE, 15, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 15, PIXEL_SIZE, 45, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 60, PIXEL_SIZE, 75, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 135, PIXEL_SIZE, 90, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 225, PIXEL_SIZE, 15, SOIL_COLOUR_1);

    //column 8
    graphics_draw_rectangle_filled(x + 105, y + 0, PIXEL_SIZE, 15, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 15, PIXEL_SIZE, 75, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 90, PIXEL_SIZE, 45, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 135, PIXEL_SIZE, 75, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 210, PIXEL_SIZE, 30, SOIL_COLOUR_2);

    //column 9
    graphics_draw_rectangle_filled(x + 120, y + 0, PIXEL_SIZE, 150, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 150, PIXEL_SIZE, 45, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 195, PIXEL_SIZE, 45, SOIL_COLOUR_1);

    //column 10
    graphics_draw_rectangle_filled(x + 135, y + 0, PIXEL_SIZE, 15, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 15, PIXEL_SIZE, 135, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 150, PIXEL_SIZE, 90, SOIL_COLOUR_1);

    //column 11
    graphics_draw_rectangle_filled(x + 150, y + 0, PIXEL_SIZE, 240, SOIL_COLOUR_1);

    //column 12
    graphics_draw_rectangle_filled(x + 165, y + 0, PIXEL_SIZE, 90, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 165, y + 90, PIXEL_SIZE, 150, SOIL_COLOUR_2);

    //column 13
    graphics_draw_rectangle_filled(x + 180, y + 0, PIXEL_SIZE, 15, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 15, PIXEL_SIZE, 90, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 105, PIXEL_SIZE, 135, SOIL_COLOUR_1);

    //column 14
    graphics_draw_rectangle_filled(x + 195, y + 0, PIXEL_SIZE, 240, SOIL_COLOUR_1);

    //column 15
    graphics_draw_rectangle_filled(x + 210, y + 0, PIXEL_SIZE, 15, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 15, PIXEL_SIZE, 180, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 195, PIXEL_SIZE, 15, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 210, PIXEL_SIZE, 15, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 225, PIXEL_SIZE, 15, SOIL_COLOUR_1);

    //column 16
    graphics_draw_rectangle_filled(x + 225, y + 0, PIXEL_SIZE, 195, SOIL_COLOUR_1);
    graphics_draw_rectangle_filled(x + 225, y + 195, PIXEL_SIZE, 15, SOIL_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 210, PIXEL_SIZE, 30, SOIL_COLOUR_1);
}


/**************************************************************
 * Stone Block
 **************************************************************/
void stone_block_generator(int x, int y) {
    //row 1
    graphics_draw_rectangle_filled(x + 0, y + 0, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 0, 45, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 135, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 150, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 165, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 195, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 225, y + 0, 15, PIXEL_SIZE, STONE_COLOUR_1);

    //row 2
    graphics_draw_rectangle_filled(x + 0, y + 15, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 15, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 45, y + 15, 45, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 15, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 105, y + 15, 45, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 150, y + 15, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 165, y + 15, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 15, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 195, y + 15, 45, PIXEL_SIZE, STONE_COLOUR_1);

    //row 3
    graphics_draw_rectangle_filled(x + 0, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 45, y + 30, 45, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 90, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 30, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 150, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 165, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 195, y + 30, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 30, 30, PIXEL_SIZE, STONE_COLOUR_1);

    //row 4
    graphics_draw_rectangle_filled(x + 0, y + 45, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 45, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 30, y + 45, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 45, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 45, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 105, y + 45, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 45, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 150, y + 45, 45, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 195, y + 45, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 45, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 225, y + 45, 15, PIXEL_SIZE, STONE_COLOUR_1);

    //row 5
    graphics_draw_rectangle_filled(x + 0, y + 60, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 60, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 60, y + 60, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 60, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 60, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 60, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 120, y + 60, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 60, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 165, y + 60, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 195, y + 60, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 60, 15, PIXEL_SIZE, STONE_COLOUR_3);

    //row 6
    graphics_draw_rectangle_filled(x + 0, y + 75, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 30, y + 75, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 75, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 75, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 75, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 75, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 75, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 150, y + 75, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 165, y + 75, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 75, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 195, y + 75, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 225, y + 75, 15, PIXEL_SIZE, STONE_COLOUR_2);

    //row 7
    graphics_draw_rectangle_filled(x + 0, y + 90, 60, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 90, 45, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 90, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 90, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 150, y + 90, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 90, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 195, y + 90, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 225, y + 90, 15, PIXEL_SIZE, STONE_COLOUR_3);

    //row 8
    graphics_draw_rectangle_filled(x + 0, y + 105, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 105, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 45, y + 105, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 105, 45, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 105, y + 105, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 105, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 105, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 150, y + 105, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 165, y + 105, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 105, 60, PIXEL_SIZE, STONE_COLOUR_1);

    //row 9
    graphics_draw_rectangle_filled(x + 0, y + 120, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 30, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 60, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 75, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 120, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 150, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 165, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 120, 45, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 225, y + 120, 15, PIXEL_SIZE, STONE_COLOUR_2);

    //row 10
    graphics_draw_rectangle_filled(x + 0, y + 135, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 90, y + 135, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 135, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 165, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 180, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 195, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 135, 15, PIXEL_SIZE, STONE_COLOUR_3);

    //row 11
    graphics_draw_rectangle_filled(x + 0, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 15, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 45, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 75, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 150, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 150, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 150, y + 150, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 195, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 225, y + 150, 15, PIXEL_SIZE, STONE_COLOUR_1);

    //row 12
    graphics_draw_rectangle_filled(x + 0, y + 165, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 15, y + 165, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 165, 45, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 75, y + 165, 45, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 165, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 150, y + 165, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 165, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 195, y + 165, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 165, 30, PIXEL_SIZE, STONE_COLOUR_1);

    //row 13
    graphics_draw_rectangle_filled(x + 0, y + 180, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 180, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 180, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 180, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 180, 45, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 120, y + 180, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 180, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 150, y + 180, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 180, y + 180, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 195, y + 180, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 210, y + 180, 30, PIXEL_SIZE, STONE_COLOUR_2);

    //row 14
    graphics_draw_rectangle_filled(x + 0, y + 195, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 195, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 30, y + 195, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 195, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 75, y + 195, 45, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 195, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 135, y + 195, 45, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 195, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 195, 30, PIXEL_SIZE, STONE_COLOUR_3);

    //row 15
    graphics_draw_rectangle_filled(x + 0, y + 210, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 210, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 210, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 60, y + 210, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 210, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 210, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 210, 45, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 180, y + 210, 30, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 210, 30, PIXEL_SIZE, STONE_COLOUR_1);

    //row 16
    graphics_draw_rectangle_filled(x + 0, y + 225, 30, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 225, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 225, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 225, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 90, y + 225, 15, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 225, 15, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 120, y + 225, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 225, 45, PIXEL_SIZE, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 225, 30, PIXEL_SIZE, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 210, y + 225, 15, PIXEL_SIZE, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 225, 15, PIXEL_SIZE, STONE_COLOUR_1);
}

/**************************************************************
 * Iron Block
 **************************************************************/
void iron_block_generator(int x, int y) {
    //row 1
	graphics_draw_rectangle_filled(x + 0, y + 0, 240, PIXEL_SIZE, IRON_COLOUR_1);

    //row 2
	graphics_draw_rectangle_filled(x + 0, y + 15, 240, PIXEL_SIZE, IRON_COLOUR_1);

    //row 3
	graphics_draw_rectangle_filled(x + 0, y + 30, 60, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 60, y + 30, 15, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 30, 105, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 180, y + 30, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 195, y + 30, 15, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 210, y + 30, 30, PIXEL_SIZE, IRON_COLOUR_1);

    //row 4
	graphics_draw_rectangle_filled(x + 0, y + 45, 105, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 105, y + 45, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 120, y + 45, 15, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 135, y + 45, 105, PIXEL_SIZE, IRON_COLOUR_1);

    //row 5
	graphics_draw_rectangle_filled(x + 0, y + 60, 240, PIXEL_SIZE, IRON_COLOUR_1);

    //row 6
	graphics_draw_rectangle_filled(x + 0, y + 75, 75, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 75, y + 75, 15, PIXEL_SIZE, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 90, y + 75, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 105, y + 75, 45, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 150, y + 75, 15, PIXEL_SIZE, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 165, y + 75, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 180, y + 75, 60, PIXEL_SIZE, IRON_COLOUR_1);

    //row 7
	graphics_draw_rectangle_filled(x + 0, y + 90, 45, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 45, y + 90, 15, PIXEL_SIZE, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 60, y + 90, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 75, y + 90, 45, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 120, y + 90, 30, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 150, y + 90, 30, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 180, y + 90, 60, PIXEL_SIZE, IRON_COLOUR_1);

    //row 8
	graphics_draw_rectangle_filled(x + 0, y + 105, 240, PIXEL_SIZE, IRON_COLOUR_1);

    //row 9
	graphics_draw_rectangle_filled(x + 0, y + 120, 15, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 15, y + 120, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 30, y + 120, 15, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 45, y + 120, 75, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 120, y + 120, 15, PIXEL_SIZE, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 135, y + 120, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 150, y + 120, 90, PIXEL_SIZE, IRON_COLOUR_1);

    //row 10
	graphics_draw_rectangle_filled(x + 0, y + 135, 105, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 105, y + 135, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 120, y + 135, 45, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 165, y + 135, 75, PIXEL_SIZE, IRON_COLOUR_1);

    //row 11
	graphics_draw_rectangle_filled(x + 0, y + 150, 60, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 60, y + 150, 15, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 150, 165, PIXEL_SIZE, IRON_COLOUR_1);

    //row 12
	graphics_draw_rectangle_filled(x + 0, y + 165, 165, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 165, y + 165, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 180, y + 165, 15, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 195, y + 165, 45, PIXEL_SIZE, IRON_COLOUR_1);

    //row 13
	graphics_draw_rectangle_filled(x + 0, y + 180, 120, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 120, y + 180, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 135, y + 180, 15, PIXEL_SIZE, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 150, y + 180, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 165, y + 180, 45, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 210, y + 180, 30, PIXEL_SIZE, IRON_COLOUR_1);

    //row 14
	graphics_draw_rectangle_filled(x + 0, y + 195, 45, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 45, y + 195, 15, PIXEL_SIZE, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 60, y + 195, 15, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 195, 60, PIXEL_SIZE, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 135, y + 195, 30, PIXEL_SIZE, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 165, y + 195, 75, PIXEL_SIZE, IRON_COLOUR_1);

    //row 15
	graphics_draw_rectangle_filled(x + 0, y + 210, 240, PIXEL_SIZE, IRON_COLOUR_1);

    //row 16
	graphics_draw_rectangle_filled(x + 0, y + 225, 240, PIXEL_SIZE, IRON_COLOUR_1);
}

/**************************************************************
 * Diamond Block
 **************************************************************/
void diamond_block_generator(int x, int y) {
	//row 1
	graphics_draw_rectangle_filled(x + 0, y + 0, 240, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 2
	graphics_draw_rectangle_filled(x + 0, y + 15, 240, PIXEL_SIZE, DIAMOND_COLOUR_1);

	//row 3
	graphics_draw_rectangle_filled(x + 0, y + 30, 60, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 60, y + 30, 15, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 30, 105, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 180, y + 30, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 195, y + 30, 15, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 210, y + 30, 30, PIXEL_SIZE, DIAMOND_COLOUR_1);

	//row 4
	graphics_draw_rectangle_filled(x + 0, y + 45, 105, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 105, y + 45, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 120, y + 45, 15, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 135, y + 45, 105, PIXEL_SIZE, DIAMOND_COLOUR_1);

	//row 5
	graphics_draw_rectangle_filled(x + 0, y + 60, 240, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 6
	graphics_draw_rectangle_filled(x + 0, y + 75, 75, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 75, y + 75, 15, PIXEL_SIZE, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 90, y + 75, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 105, y + 75, 45, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 150, y + 75, 15, PIXEL_SIZE, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 165, y + 75, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 180, y + 75, 60, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 7
	graphics_draw_rectangle_filled(x + 0, y + 90, 45, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 45, y + 90, 15, PIXEL_SIZE, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 60, y + 90, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 75, y + 90, 45, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 120, y + 90, 30, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 150, y + 90, 30, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 180, y + 90, 60, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 8
	graphics_draw_rectangle_filled(x + 0, y + 105, 240, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 9
	graphics_draw_rectangle_filled(x + 0, y + 120, 15, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 15, y + 120, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 30, y + 120, 15, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 45, y + 120, 75, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 120, y + 120, 15, PIXEL_SIZE, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 135, y + 120, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 150, y + 120, 90, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 10
	graphics_draw_rectangle_filled(x + 0, y + 135, 105, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 105, y + 135, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 120, y + 135, 45, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 165, y + 135, 75, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 11
	graphics_draw_rectangle_filled(x + 0, y + 150, 60, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 60, y + 150, 15, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 150, 165, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 12
	graphics_draw_rectangle_filled(x + 0, y + 165, 165, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 165, y + 165, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 180, y + 165, 15, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 195, y + 165, 45, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 13
	graphics_draw_rectangle_filled(x + 0, y + 180, 120, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 120, y + 180, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 135, y + 180, 15, PIXEL_SIZE, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 150, y + 180, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 165, y + 180, 45, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 210, y + 180, 30, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 14
	graphics_draw_rectangle_filled(x + 0, y + 195, 45, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 45, y + 195, 15, PIXEL_SIZE, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 60, y + 195, 15, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 195, 60, PIXEL_SIZE, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 135, y + 195, 30, PIXEL_SIZE, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 165, y + 195, 75, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 15
	graphics_draw_rectangle_filled(x + 0, y + 210, 240, PIXEL_SIZE, DIAMOND_COLOUR_1);

    //row 16
	graphics_draw_rectangle_filled(x + 0, y + 225, 240, PIXEL_SIZE, DIAMOND_COLOUR_1);
}
