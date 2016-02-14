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

//colours used for wood block
#define WOOD_COLOUR_1 SADDLE_BROWN
#define WOOD_COLOUR_2 BLACK

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

#define WIDTH 15
#define LENGTH 15

void clear_block(int x, int y) {
	graphics_draw_rectangle_filled(x, y, 240, 240, WHITE);
}

/**************************************************************
 * Wood Block
 **************************************************************/
void wood_block_generator(int x, int y) {
    //column 1
    graphics_draw_rectangle_filled(x + 0, y + 0, WIDTH, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 0, y + 45, WIDTH, 105, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 0, y + 150, WIDTH, 75, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 0, y + 225, WIDTH, 15, WOOD_COLOUR_1);

    //column 2
    graphics_draw_rectangle_filled(x + 15, y + 0, WIDTH, 45, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 45, WIDTH, 30, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 15, y + 75, WIDTH, 165, WOOD_COLOUR_1);

    //column 3
    graphics_draw_rectangle_filled(x + 30, y + 0, WIDTH, 105, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 105, WIDTH, 90, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 195, WIDTH, 45, WOOD_COLOUR_1);

    //column 4
    graphics_draw_rectangle_filled(x + 45, y + 0, WIDTH, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 45, y + 15, WIDTH, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 60, WIDTH, 180, WOOD_COLOUR_1);

    //column 5
    graphics_draw_rectangle_filled(x + 60, y + 0, WIDTH, 30, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 30, WIDTH, 210, WOOD_COLOUR_1);

    //column 6
    graphics_draw_rectangle_filled(x + 75, y + 0, WIDTH, 105, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 75, y + 105, WIDTH, 30, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 135, WIDTH, 105, WOOD_COLOUR_1);

    //column 7
    graphics_draw_rectangle_filled(x + 90, y + 0, WIDTH, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 15, WIDTH, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 60, WIDTH, 75, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 135, WIDTH, 90, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 225, WIDTH, 15, WOOD_COLOUR_1);

    //column 8
    graphics_draw_rectangle_filled(x + 105, y + 0, WIDTH, 15, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 15, WIDTH, 75, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 90, WIDTH, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 135, WIDTH, 75, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 210, WIDTH, 30, WOOD_COLOUR_2);

    //column 9
    graphics_draw_rectangle_filled(x + 120, y + 0, WIDTH, 150, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 150, WIDTH, 45, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 195, WIDTH, 45, WOOD_COLOUR_1);

    //column 10
    graphics_draw_rectangle_filled(x + 135, y + 0, WIDTH, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 15, WIDTH, 135, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 150, WIDTH, 90, WOOD_COLOUR_1);

    //column 11
    graphics_draw_rectangle_filled(x + 150, y + 0, WIDTH, 240, WOOD_COLOUR_1);

    //column 12
    graphics_draw_rectangle_filled(x + 165, y + 0, WIDTH, 90, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 165, y + 90, WIDTH, 150, WOOD_COLOUR_2);

    //column 13
    graphics_draw_rectangle_filled(x + 180, y + 0, WIDTH, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 15, WIDTH, 90, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 105, WIDTH, 135, WOOD_COLOUR_1);

    //column 14
    graphics_draw_rectangle_filled(x + 195, y + 0, WIDTH, 240, WOOD_COLOUR_1);

    //column 15
    graphics_draw_rectangle_filled(x + 210, y + 0, WIDTH, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 15, WIDTH, 180, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 195, WIDTH, 15, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 210, WIDTH, 15, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 225, WIDTH, 15, WOOD_COLOUR_1);

    //column 16
    graphics_draw_rectangle_filled(x + 225, y + 0, WIDTH, 195, WOOD_COLOUR_1);
    graphics_draw_rectangle_filled(x + 225, y + 195, WIDTH, 15, WOOD_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 210, WIDTH, 30, WOOD_COLOUR_1);
}

/**************************************************************
 * Stone Block
 **************************************************************/
void stone_block_generator(int x, int y) {
    //row 1
    graphics_draw_rectangle_filled(x + 0, y + 0, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 0, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 0, 45, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 0, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 0, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 0, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 135, y + 0, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 150, y + 0, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 165, y + 0, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 0, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 195, y + 0, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 0, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 225, y + 0, 15, LENGTH, STONE_COLOUR_1);

    //row 2
    graphics_draw_rectangle_filled(x + 0, y + 15, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 15, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 45, y + 15, 45, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 15, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 105, y + 15, 45, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 150, y + 15, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 165, y + 15, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 15, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 195, y + 15, 45, LENGTH, STONE_COLOUR_1);

    //row 3
    graphics_draw_rectangle_filled(x + 0, y + 30, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 30, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 30, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 45, y + 30, 45, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 90, y + 30, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 30, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 30, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 150, y + 30, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 165, y + 30, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 30, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 195, y + 30, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 30, 30, LENGTH, STONE_COLOUR_1);

    //row 4
    graphics_draw_rectangle_filled(x + 0, y + 45, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 45, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 30, y + 45, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 45, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 45, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 105, y + 45, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 45, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 150, y + 45, 45, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 195, y + 45, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 45, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 225, y + 45, 15, LENGTH, STONE_COLOUR_1);

    //row 5
    graphics_draw_rectangle_filled(x + 0, y + 60, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 60, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 60, y + 60, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 60, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 60, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 60, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 120, y + 60, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 60, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 165, y + 60, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 195, y + 60, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 60, 15, LENGTH, STONE_COLOUR_3);

    //row 6
    graphics_draw_rectangle_filled(x + 0, y + 75, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 30, y + 75, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 75, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 75, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 90, y + 75, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 75, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 75, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 150, y + 75, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 165, y + 75, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 75, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 195, y + 75, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 225, y + 75, 15, LENGTH, STONE_COLOUR_2);

    //row 7
    graphics_draw_rectangle_filled(x + 0, y + 90, 60, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 90, 45, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 105, y + 90, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 90, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 150, y + 90, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 90, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 195, y + 90, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 225, y + 90, 15, LENGTH, STONE_COLOUR_3);

    //row 8
    graphics_draw_rectangle_filled(x + 0, y + 105, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 105, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 45, y + 105, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 105, 45, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 105, y + 105, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 105, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 135, y + 105, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 150, y + 105, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 165, y + 105, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 105, 60, LENGTH, STONE_COLOUR_1);

    //row 9
    graphics_draw_rectangle_filled(x + 0, y + 120, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 30, y + 120, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 120, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 60, y + 120, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 75, y + 120, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 120, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 120, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 120, y + 120, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 120, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 150, y + 120, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 165, y + 120, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 120, 45, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 225, y + 120, 15, LENGTH, STONE_COLOUR_2);

    //row 10
    graphics_draw_rectangle_filled(x + 0, y + 135, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 135, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 135, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 135, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 135, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 90, y + 135, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 135, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 135, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 165, y + 135, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 180, y + 135, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 195, y + 135, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 135, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 135, 15, LENGTH, STONE_COLOUR_3);

    //row 11
    graphics_draw_rectangle_filled(x + 0, y + 150, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 15, y + 150, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 150, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 45, y + 150, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 150, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 75, y + 150, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 150, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 150, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 150, y + 150, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 150, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 195, y + 150, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 150, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 225, y + 150, 15, LENGTH, STONE_COLOUR_1);

    //row 12
    graphics_draw_rectangle_filled(x + 0, y + 165, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 15, y + 165, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 165, 45, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 75, y + 165, 45, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 120, y + 165, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 150, y + 165, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 165, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 195, y + 165, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 165, 30, LENGTH, STONE_COLOUR_1);

    //row 13
    graphics_draw_rectangle_filled(x + 0, y + 180, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 180, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 30, y + 180, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 180, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 75, y + 180, 45, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 120, y + 180, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 180, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 150, y + 180, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 180, y + 180, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 195, y + 180, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 210, y + 180, 30, LENGTH, STONE_COLOUR_2);

    //row 14
    graphics_draw_rectangle_filled(x + 0, y + 195, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 15, y + 195, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 30, y + 195, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 60, y + 195, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 75, y + 195, 45, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 195, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 135, y + 195, 45, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 180, y + 195, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 210, y + 195, 30, LENGTH, STONE_COLOUR_3);

    //row 15
    graphics_draw_rectangle_filled(x + 0, y + 210, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 210, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 210, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 60, y + 210, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 90, y + 210, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 120, y + 210, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 210, 45, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 180, y + 210, 30, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 210, y + 210, 30, LENGTH, STONE_COLOUR_1);

    //row 16
    graphics_draw_rectangle_filled(x + 0, y + 225, 30, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 30, y + 225, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 45, y + 225, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 60, y + 225, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 90, y + 225, 15, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 105, y + 225, 15, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 120, y + 225, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 135, y + 225, 45, LENGTH, STONE_COLOUR_1);
    graphics_draw_rectangle_filled(x + 180, y + 225, 30, LENGTH, STONE_COLOUR_3);
    graphics_draw_rectangle_filled(x + 210, y + 225, 15, LENGTH, STONE_COLOUR_2);
    graphics_draw_rectangle_filled(x + 225, y + 225, 15, LENGTH, STONE_COLOUR_1);
}

/**************************************************************
 * Iron Block
 **************************************************************/
void iron_block_generator(int x, int y) {
    //row 1
	graphics_draw_rectangle_filled(x + 0, y + 0, 240, LENGTH, IRON_COLOUR_1);

    //row 2
	graphics_draw_rectangle_filled(x + 0, y + 15, 240, LENGTH, IRON_COLOUR_1);

    //row 3
	graphics_draw_rectangle_filled(x + 0, y + 30, 60, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 60, y + 30, 15, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 30, 105, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 180, y + 30, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 195, y + 30, 15, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 210, y + 30, 30, LENGTH, IRON_COLOUR_1);

    //row 4
	graphics_draw_rectangle_filled(x + 0, y + 45, 105, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 105, y + 45, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 120, y + 45, 15, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 135, y + 45, 105, LENGTH, IRON_COLOUR_1);

    //row 5
	graphics_draw_rectangle_filled(x + 0, y + 60, 240, LENGTH, IRON_COLOUR_1);

    //row 6
	graphics_draw_rectangle_filled(x + 0, y + 75, 75, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 75, y + 75, 15, LENGTH, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 90, y + 75, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 105, y + 75, 45, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 150, y + 75, 15, LENGTH, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 165, y + 75, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 180, y + 75, 60, LENGTH, IRON_COLOUR_1);

    //row 7
	graphics_draw_rectangle_filled(x + 0, y + 90, 45, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 45, y + 90, 15, LENGTH, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 60, y + 90, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 75, y + 90, 45, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 120, y + 90, 30, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 150, y + 90, 30, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 180, y + 90, 60, LENGTH, IRON_COLOUR_1);

    //row 8
	graphics_draw_rectangle_filled(x + 0, y + 105, 240, LENGTH, IRON_COLOUR_1);

    //row 9
	graphics_draw_rectangle_filled(x + 0, y + 120, 15, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 15, y + 120, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 30, y + 120, 15, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 45, y + 120, 75, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 120, y + 120, 15, LENGTH, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 135, y + 120, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 150, y + 120, 90, LENGTH, IRON_COLOUR_1);

    //row 10
	graphics_draw_rectangle_filled(x + 0, y + 135, 105, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 105, y + 135, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 120, y + 135, 45, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 165, y + 135, 75, LENGTH, IRON_COLOUR_1);

    //row 11
	graphics_draw_rectangle_filled(x + 0, y + 150, 60, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 60, y + 150, 15, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 150, 165, LENGTH, IRON_COLOUR_1);

    //row 12
	graphics_draw_rectangle_filled(x + 0, y + 165, 165, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 165, y + 165, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 180, y + 165, 15, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 195, y + 165, 45, LENGTH, IRON_COLOUR_1);

    //row 13
	graphics_draw_rectangle_filled(x + 0, y + 180, 120, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 120, y + 180, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 135, y + 180, 15, LENGTH, IRON_COLOUR_2);
	graphics_draw_rectangle_filled(x + 150, y + 180, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 165, y + 180, 45, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 210, y + 180, 30, LENGTH, IRON_COLOUR_1);

    //row 14
	graphics_draw_rectangle_filled(x + 0, y + 195, 45, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 45, y + 195, 15, LENGTH, IRON_COLOUR_3);
	graphics_draw_rectangle_filled(x + 60, y + 195, 15, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 195, 60, LENGTH, IRON_COLOUR_1);
	graphics_draw_rectangle_filled(x + 135, y + 195, 30, LENGTH, IRON_COLOUR_4);
	graphics_draw_rectangle_filled(x + 165, y + 195, 75, LENGTH, IRON_COLOUR_1);

    //row 15
	graphics_draw_rectangle_filled(x + 0, y + 210, 240, LENGTH, IRON_COLOUR_1);

    //row 16
	graphics_draw_rectangle_filled(x + 0, y + 225, 240, LENGTH, IRON_COLOUR_1);
}

/**************************************************************
 * Diamond Block
 **************************************************************/
void diamond_block_generator(int x, int y) {
	//row 1
	graphics_draw_rectangle_filled(x + 0, y + 0, 240, LENGTH, DIAMOND_COLOUR_1);

    //row 2
	graphics_draw_rectangle_filled(x + 0, y + 15, 240, LENGTH, DIAMOND_COLOUR_1);

	//row 3
	graphics_draw_rectangle_filled(x + 0, y + 30, 60, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 60, y + 30, 15, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 30, 105, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 180, y + 30, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 195, y + 30, 15, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 210, y + 30, 30, LENGTH, DIAMOND_COLOUR_1);

	//row 4
	graphics_draw_rectangle_filled(x + 0, y + 45, 105, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 105, y + 45, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 120, y + 45, 15, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 135, y + 45, 105, LENGTH, DIAMOND_COLOUR_1);

	//row 5
	graphics_draw_rectangle_filled(x + 0, y + 60, 240, LENGTH, DIAMOND_COLOUR_1);

    //row 6
	graphics_draw_rectangle_filled(x + 0, y + 75, 75, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 75, y + 75, 15, LENGTH, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 90, y + 75, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 105, y + 75, 45, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 150, y + 75, 15, LENGTH, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 165, y + 75, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 180, y + 75, 60, LENGTH, DIAMOND_COLOUR_1);

    //row 7
	graphics_draw_rectangle_filled(x + 0, y + 90, 45, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 45, y + 90, 15, LENGTH, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 60, y + 90, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 75, y + 90, 45, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 120, y + 90, 30, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 150, y + 90, 30, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 180, y + 90, 60, LENGTH, DIAMOND_COLOUR_1);

    //row 8
	graphics_draw_rectangle_filled(x + 0, y + 105, 240, LENGTH, DIAMOND_COLOUR_1);

    //row 9
	graphics_draw_rectangle_filled(x + 0, y + 120, 15, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 15, y + 120, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 30, y + 120, 15, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 45, y + 120, 75, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 120, y + 120, 15, LENGTH, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 135, y + 120, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 150, y + 120, 90, LENGTH, DIAMOND_COLOUR_1);

    //row 10
	graphics_draw_rectangle_filled(x + 0, y + 135, 105, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 105, y + 135, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 120, y + 135, 45, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 165, y + 135, 75, LENGTH, DIAMOND_COLOUR_1);

    //row 11
	graphics_draw_rectangle_filled(x + 0, y + 150, 60, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 60, y + 150, 15, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 150, 165, LENGTH, DIAMOND_COLOUR_1);

    //row 12
	graphics_draw_rectangle_filled(x + 0, y + 165, 165, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 165, y + 165, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 180, y + 165, 15, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 195, y + 165, 45, LENGTH, DIAMOND_COLOUR_1);

    //row 13
	graphics_draw_rectangle_filled(x + 0, y + 180, 120, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 120, y + 180, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 135, y + 180, 15, LENGTH, DIAMOND_COLOUR_2);
	graphics_draw_rectangle_filled(x + 150, y + 180, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 165, y + 180, 45, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 210, y + 180, 30, LENGTH, DIAMOND_COLOUR_1);

    //row 14
	graphics_draw_rectangle_filled(x + 0, y + 195, 45, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 45, y + 195, 15, LENGTH, DIAMOND_COLOUR_3);
	graphics_draw_rectangle_filled(x + 60, y + 195, 15, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 75, y + 195, 60, LENGTH, DIAMOND_COLOUR_1);
	graphics_draw_rectangle_filled(x + 135, y + 195, 30, LENGTH, DIAMOND_COLOUR_4);
	graphics_draw_rectangle_filled(x + 165, y + 195, 75, LENGTH, DIAMOND_COLOUR_1);

    //row 15
	graphics_draw_rectangle_filled(x + 0, y + 210, 240, LENGTH, DIAMOND_COLOUR_1);

    //row 16
	graphics_draw_rectangle_filled(x + 0, y + 225, 240, LENGTH, DIAMOND_COLOUR_1);
}
