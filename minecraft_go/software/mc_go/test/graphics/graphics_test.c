#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rs232.h"
#include "Colours.h"
#include "ColourPallette.h"

#define YRES 480
#define XRES 640
#define TRUE 1
#define FALSE 0


int graphics_test()
{
	//ProgramPalette(BLUE,0x000000FF);
int i;
for(i=0; i <= 480;i++){
	HLine(0,i,640,WHITE);
}

Line2(0,0, 400,400, BLUE);
HLine(0,100,640,BLUE);
VLine2(110,0,450,BLUE);
VLine(110,0,450, GREEN);
Line2(640,480, 400,400, BLUE);
Line(0,0, 400, 400, GREEN);
Line(640,480, 400,400, GREEN);

Triangle(110,10,100,100,150,400, PINK);

//FillRectangle(10,10,10,300,300,10, 300,300, GOLD);


//Fonts bigger than 5x7 are a work in progress
OutGraphicsCharFont2a(300,100, BLUE, ORANGE, 'G', FALSE);


	return 0;
}

