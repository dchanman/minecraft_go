#include "graphics.h"

// graphics registers all address begin with '8' so as to by pass data cache on NIOS

#define GraphicsCommandReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg   		(*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg   			(*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg   			(*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg   			(*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg   			(*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg   		(*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg   	(*(volatile unsigned short int *)(0x84000010))

/************************************************************************************************
** This macro pauses until the graphics chip status register indicates that it is idle
***********************************************************************************************/

#define WAIT_FOR_GRAPHICS		while((GraphicsStatusReg & 0x0001) != 0x0001);

//Here are some software routines to drive some simple graphics functions

// #defined constants representing values we write to the graphics 'command' register to get
// it to draw something. You will add more values as you add hardware to the graphics chip
// Note DrawHLine, DrawVLine and DrawLine at the moment do nothing - you will modify these

#define DrawHLine		0x1
#define DrawVLine		0x2
#define DrawLine		0x3
#define	PutAPixel		0xA
#define	GetAPixel		0xB
#define	ProgramPaletteColour    0x10

// defined constants representing colours pre-programmed into colour palette
// there are 256 colours but only 8 are shown below, we write these to the colour registers
//
// the header files "Colours.h" contains constants for all 256 colours
// while the course file ColourPaletteData.c contains the 24 bit RGB data
// that is pre-programmed into the palette

#define	BLACK			0
#define	WHITE			1
#define	RED				2
#define	LIME			3
#define	BLUE			4
#define	YELLOW			5
#define	CYAN			6
#define	MAGENTA			7

/*******************************************************************************************
* This function writes a single pixel to the x,y coords specified using the specified colour
* Note colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
********************************************************************************************/
void WriteAPixel(int x, int y, int Colour)
{
	WAIT_FOR_GRAPHICS;				// is graphics ready for new command

	GraphicsX1Reg = x;				// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour;			// set pixel colour
	GraphicsCommandReg = PutAPixel;			// give graphics "write pixel" command
}

/*********************************************************************************************
* This function read a single pixel from the x,y coords specified and returns its colour
* Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
*********************************************************************************************/

int ReadAPixel(int x, int y)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS;			// is graphics done reading pixel
	return (int)(GraphicsColourReg) ;	// return the palette number (colour)
}


/**********************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
**
************************************************************************************/

void ProgramPalette(int PaletteNumber, int RGB)
{
    WAIT_FOR_GRAPHICS;
    GraphicsColourReg = PaletteNumber;
    GraphicsX1Reg = RGB >> 16   ;        // program red value in ls.8 bit of X1 reg
    GraphicsY1Reg = RGB ;                // program green and blue into ls 16 bit of Y1 reg
    GraphicsCommandReg = ProgramPaletteColour; // issue command
}

/********************************************************************************************* 
This function draw a horizontal line, 1 pixel at a time starting at the x,y coords specified
*********************************************************************************************/

void HLine(int x1, int y1, int length, int Colour)
{
		WAIT_FOR_GRAPHICS;				// is graphics ready for new command

		GraphicsX1Reg = x1;				// write coords to x1, y1
		GraphicsY1Reg = y1;
		GraphicsX2Reg = x1+length;
		GraphicsColourReg = Colour;			// set pixel colour
		GraphicsCommandReg = DrawHLine;			// give graphics "write pixel" command
}

/********************************************************************************************* 
This function draw a vertical line, 1 pixel at a time starting at the x,y coords specified
*********************************************************************************************/

void VLine(int x1, int y1, int length, int Colour)
{
	int i;

	for(i = y1; i < y1+length; i++ )
		WriteAPixel(x1, i, Colour);
}

void VLine2(int x1, int y1, int length, int Colour)
{
		WAIT_FOR_GRAPHICS;				// is graphics ready for new command

		GraphicsX1Reg = x1;				// write coords to x1, y1
		GraphicsY1Reg = y1;
		GraphicsY2Reg = y1+length;
		GraphicsColourReg = Colour;			// set pixel colour
		GraphicsCommandReg = DrawVLine;			// give graphics "write pixel" command
}


/*******************************************************************************
** Implementation of Bresenhams line drawing algorithm
*******************************************************************************/

int abs(int a)
{
    if(a < 0)
        return -a ;
    else
        return a ;
}

int sign(int a)
{
    if(a < 0)
        return -1 ;
    else if (a == 0)
        return 0 ;
    else
        return 1 ;
}


void Line(int x1, int y1, int x2, int y2, int Colour)
{
    int x = x1;
    int y = y1;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int s1 = sign(x2 - x1);
    int s2 = sign(y2 - y1);
    int i, temp, interchange = 0, error ;

// if x1=x2 and y1=y2 then it is a line of zero length

    if(dx == 0 && dy == 0)
        return ;

 // must be a complex line so use bresenhams algorithm
    else    {

// swap delta x and delta y depending upon slop of line

        if(dy > dx) {
            temp = dx ;
            dx = dy ;
            dy = temp ;
            interchange = 1 ;
        }

// initialise the error term to compensate for non-zero intercept

        error = (dy << 1) - dx ;    // (2 * dy) - dx

// main loop
        for(i = 1; i <= dx; i++)    {
            WriteAPixel(x, y, Colour);

            while(error >= 0)   {
                if(interchange == 1)
                    x += s1 ;
                else
                    y += s2 ;

                error -= (dx << 1) ;    // times 2
            }

            if(interchange == 1)
                y += s2 ;
            else
                x += s1 ;

            error += (dy << 1) ;    // times 2
        }
    }
}

void Line2(int x1, int y1, int x2, int y2, int Colour)
{
	WAIT_FOR_GRAPHICS;				// is graphics ready for new command

		GraphicsX1Reg = x1;				// write coords to x1, y1
		GraphicsY1Reg = y1;
		GraphicsX2Reg = x2;
		GraphicsY2Reg = y2;
		GraphicsColourReg = Colour;			// set pixel colour
		GraphicsCommandReg = DrawLine;			// give graphics "write pixel" command
}

void Triangle(int x1, int y1, int x2, int y2, int x3, int y3, int Colour)
{
	Line2(x1, y1, x2, y2, Colour);
	Line2(x1, y1, x3, y3, Colour);
	Line2(x2, y2, x3, y3, Colour);
}

void Rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int Colour)
{

	Line2(x1,y1,x2,y2, Colour);
	Line2(x1,y1,x3,y3, Colour);
	Line2(x2,y2,x4,y4, Colour);
	Line2(x3,y3,x4,y4,Colour);

}

void graphics_draw_rectangle_border(int x, int y, int width, int height, int colour)
{
	VLine2(x, y, height, colour);
	VLine2(x + width, y, height, colour);
	HLine(x, y, width, colour);
	HLine(x, y + height, width, colour);
}

void graphics_draw_rectangle_filled(int x, int y, int width, int height, int colour)
{
	int y0;

	for (y0 = y; y0 < (y + height); y0++) {
		Line2(x, y0, x+width, y0, colour);
	}
}

void FillRectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int Colour)
{

	Line2(x1,y1,x2,y2, Colour);
	Line2(x1,y1,x3,y3, Colour);
	Line2(x2,y2,x4,y4, Colour);
	Line2(x3,y3,x4,y4,Colour);



}

void graphics_clear_screen() {
	graphics_draw_rectangle_filled(0, 0, GRAPHICS_PIXEL_WIDTH, GRAPHICS_PIXEL_HEIGHT, GRAPHICS_BACKGROUND_COLOUR);
}

void graphics_fill_screen(int colour) {
	graphics_draw_rectangle_filled(0, 0, GRAPHICS_PIXEL_WIDTH, GRAPHICS_PIXEL_HEIGHT, colour);
}

void FillRectangleWBorder(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int Colour)
{

	Line2(x1,y1,x2,y2, Colour);
	Line2(x1,y1,x3,y3, Colour);
	Line2(x2,y2,x4,y4, Colour);
	Line2(x3,y3,x4,y4,Colour);

}



