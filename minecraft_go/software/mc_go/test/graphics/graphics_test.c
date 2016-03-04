#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rs232.h"
#include "Colours.h"
#include "ColourPallette.h"
#include "font.h"

#define YRES 480
#define XRES 800
#define TRUE 1
#define FALSE 0


int graphics_test() {
	//ProgramPalette(BLUE,0x000000FF);

	int i = 0;
	int x1,x2,y1,y2, color;

	graphics_clear_screen();

	//CRAZY DEMO CODE
	/*
	while(1) {
		x1 = rand() % XRES;
		y1 = rand() % YRES;
		x2 = rand() % XRES;
		y2 = rand() % YRES;

		color = rand() % 100;
		Line2(x1, y1, x2, y2, color);

	}
*/
	Line2(0, 0, 400, 400, BLUE);
	HLine(0, 100, 640, BLUE);
	VLine2(110, 0, 450, BLUE);
	VLine(110, 0, 450, GREEN);
	Line2(640, 480, 400, 400, BLUE);
	Line(0, 0, 400, 400, GREEN);
	Line(640, 480, 400, 400, GREEN);


	Triangle(110, 10, 100, 100, 150, 400, PINK);

	graphics_draw_rectangle_filled(400, 200, 50, 10, GOLD);
	graphics_draw_rectangle_border(400, 200, 50, 10, OLIVE);

//Fonts bigger than 5x7 are a work in progress
	graphics_char_font_2(300, 100, BLUE, ORANGE, 'A', FALSE);
	graphics_char_font_3(300, 300, BLUE, ORANGE, 'A', FALSE);

	graphics_char_font_4(300, 300, BLUE, ORANGE, 'A', FALSE);
	graphics_char_font_5(300, 100, BLUE, ORANGE, 'A', FALSE);

	return 0;
}

