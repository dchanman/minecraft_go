/*
 * graphics.h
 *
 *  Created on: Feb 9, 2016
 *      Author: derek
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Colours.h"

#define GRAPHICS_PIXEL_WIDTH	800
#define GRAPHICS_PIXEL_HEIGHT	480

#define GRAPHICS_BACKGROUND_COLOUR	BLACK

void graphics_draw_rectangle_border(int x, int y, int width, int height, int colour);
void graphics_draw_rectangle_filled(int x, int y, int width, int height, int colour);
void graphics_clear_screen();
void graphics_fill_screen(int colour);

void OutGraphicsCharFont1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont2a(int x, int y, int colour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont3(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont4(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont5(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);


#endif /* GRAPHICS_H_ */
