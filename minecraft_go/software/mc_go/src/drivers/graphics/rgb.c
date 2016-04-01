/*
 * rgb.c
 *
 *  Created on: Mar 17, 2016
 *      Author: derek
 */

#include <stdio.h>
#include "rgb.h"
#include "Colours.h"
#include "graphics.h"

#define RGB_THRESHOLD	64

void rgb_init() {
	/* Initializes our colour pallette to use all 256 colours */
	int r;
	int g;
	int b;

	int pallette_number;
	int rgb;

	for (r = 0; r < 0x8; r++) {
		for (g = 0; g < 0x8; g++) {
			for (b = 0; b < 0x4; b++) {
				pallette_number = 0;
				pallette_number |= (r << 5);
				pallette_number |= (g << 2);
				pallette_number |= b;
				rgb = 0;
				rgb |= ((0xFF / 0x8 * r) << 16);
				rgb |= ((0xFF / 0x8 * g) << 8);
				rgb |= (0xFF / 0x4 * b);
				//printf("[%s]: Pallette (%d): RGB <0x%0X>\n", __func__, pallette_number, rgb);

				graphics_program_pallette(pallette_number, rgb);
			}
		}
	}
}

/* Janky conversion from RGB bytes to the hardcoded colours we use */
int rgb_to_8bit(unsigned char red_byte, unsigned char green_byte, unsigned char blue_byte) {

	int rgb;

	rgb = (0xE0 & red_byte) | ((0xE0 & green_byte) >> 3) | ((0xC0 & blue_byte) >> 6);

	return rgb;
}
