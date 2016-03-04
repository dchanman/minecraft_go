#include "font.h"

#define YRES 480
#define XRES 800
#define TRUE 1
#define FALSE 0


#define FONT2_XPIXELS	10				// width of Font2 characters in pixels (no spacing)
#define FONT2_YPIXELS	14				// height of Font2 characters in pixels (no spacing)

#define FONT3_XPIXELS	22				// width of Font2 characters in pixels (no spacing)
#define FONT3_YPIXELS	40				// height of Font2 characters in pixels (no spacing)





extern const unsigned short int Font10x14[][14];
extern const unsigned char Font22x40[];
extern const unsigned char Font16x27[];
extern const unsigned char Font38x59[];


/******************************************************************************************************************************
** This function draws a single ASCII character at the coord specified using the colour specified
** OutGraphicsCharFont2(100,100, RED, 'A', TRUE, FALSE, 1, 1) ;	// display upper case 'A' in RED at coords 100,100, erase background
** no scroll, scale x,y= 1,1
**
******************************************************************************************************************************/
void graphics_char_font_2(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = fontcolour;
	register int 	BitMask,
					theCharacter = c,
					j,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT2_YPIXELS;
		theColumn = FONT2_XPIXELS;

		for(row = 0; row < theRow ; row ++)	{
			pixels = Font10x14[theCharacter][row] ;		     								// get the pixels for row 0 of the character to be displayed
			BitMask = 512 ;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn;   )  	{
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel(theX+column, theY+row, theColour) ;
				else {																		// if not a valid pixel, do we erase or leave it along (no erase)
					if(Erase == TRUE)
						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
					// else leave it alone
				}
					column ++ ;
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void graphics_char_font_3(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int row, column, theX = x, theY = y ;
	register int pixel1, pixel2, pixel3, pixels ;
	register char theColour = fontcolour  ;
	register int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother
// XRES and YRES are #defined to be 800 and 480 respectively
    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
        return ;


// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		theC = theC * 120;

		for(row = 0; (char)(row) < (char)(40); row ++)	{

			// get the bit pattern for row 0 of the character from the software font

			pixel1 = Font22x40[theC + 3*row];
			pixel2 = Font22x40[theC + 3*row +1];
			pixel3 = Font22x40[theC + 3*row +2];
			pixels = (pixel1 << 16)+ (pixel2 << 8) +pixel3;
			BitMask = 2097152 * 4 ;

			for(column = 0; (char)(column) < (char)(22); column ++)	{

// if a pixel in the character display it
				if((pixels & BitMask))
					WriteAPixel(theX+column, theY+row, theColour) ;

				else {
					if(Erase == TRUE)

// if pixel is part of background (not part of character)
// erase the background to value of variable BackGroundColour

						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void graphics_char_font_4(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int row, column, theX = x, theY = y ;
	register int pixel1, pixel2, pixels ;
	register char theColour = fontcolour  ;
	register int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother
// XRES and YRES are #defined to be 800 and 480 respectively
    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
        return ;


// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		theC = theC * 54;

		for(row = 0; (char)(row) < (char)(27); row ++)	{

			// get the bit pattern for row 0 of the character from the software font

			pixel1 = Font16x27[theC + 2*row];
			pixel2 = Font16x27[theC + 2*row +1];
			pixels = (pixel1 << 8)+ pixel2;
			BitMask = 65536;

			for(column = 0; (char)(column) < (char)(16); column ++)	{

// if a pixel in the character display it
				if((pixels & BitMask))
					WriteAPixel(theX+column, theY+row, theColour) ;

				else {
					if(Erase == TRUE)

// if pixel is part of background (not part of character)
// erase the background to value of variable BackGroundColour

						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void graphics_char_font_5(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int row, column, theX = x, theY = y ;
	register int pixel1, pixel2, pixel3, pixel4, pixels ;
	register char theColour = fontcolour  ;
	register unsigned int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother
// XRES and YRES are #defined to be 800 and 480 respectively
    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
        return ;


// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		theC = theC * 236;

		for(row = 0; (char)(row) < (char)(59); row ++)	{

			// get the bit pattern for row 0 of the character from the software font

			pixel1 = Font38x59[theC + 4*row];
			pixel2 = Font38x59[theC + 4*row +1];
			pixel3 = Font38x59[theC + 4*row +2];
			pixel4 = Font38x59[theC + 4*row +3];
			pixels = (pixel1 << 24)+ (pixel2 << 16) +(pixel3 << 8) + pixel4;
			BitMask = 2147483648;

			for(column = 0; (char)(column) < (char)(38); column ++)	{

// if a pixel in the character display it
				if((pixels & BitMask))
					WriteAPixel(theX+column, theY+row, theColour) ;

				else {
					if(Erase == TRUE)

// if pixel is part of background (not part of character)
// erase the background to value of variable BackGroundColour

						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

