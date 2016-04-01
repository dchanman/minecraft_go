/*
 * bitmap.c
 *
 *  Created on: Mar 17, 2016
 *      Author: derek
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitmap.h"
#include "rgb.h"
#include "graphics.h"
#include "sdcard.h"

typedef struct bitmap_rgb {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} bitmap_rgb_t;

static int bitmap_draw_scaled(const char * bitmap, const int scaled_width, const int scaled_height, const int origin_x, const int origin_y);

int bitmap_import_image(const char * filename, char ** data_out, int * length, int * data_start_offset) {
	char header[STEGO_ENGINE_BMP_HEADER_SIZE];
	char filename_buffer[32];
	char * filedata;
	short int fh;
	int len;
	int read;
	int h;
	int w;

	snprintf(filename_buffer, sizeof(filename_buffer), "%s", filename);

	if (sdcard_open(&fh, filename_buffer)) {
		printf("Could not open\n");
		return -1;
	}

	if (sdcard_read(fh, header, sizeof(header)) < 0) {
		printf("Could not read\n");
		return -1;
	}

	bitmap_process_header(header, &len, data_start_offset, &w, &h);

	filedata = malloc(len*sizeof(char));
	if (filedata == NULL) {
		printf("Not enough memory to import file data");
		return -1;
	}
	memset(filedata, '\0', len*sizeof(char));

	/* Copy in the whole file. We close and reopen the file instead of doing a fseek. sdcard also mangles our filename */
	sdcard_close(fh);
	snprintf(filename_buffer, sizeof(filename_buffer), "%s", filename);
	if (sdcard_open(&fh, filename_buffer)) {
		printf("Could not open\n");
		return -1;
	}

	read = sdcard_read(fh, filedata, len);
	if (read < len) {
		printf("Could not read entire file, read <%d> of length <%d>\n", read, len);
		goto err;
	}

	*data_out = filedata;
	*length = len;

	sdcard_close(fh);

	return 0;

err:
	free(filedata);
	sdcard_close(fh);
	return -1;
}

int bitmap_export_image(const char * filename, const char * data, const int length) {
	short int fh;
	int wrote;

	if (sdcard_open(&fh, filename) != 0) {
		printf("Could not open\n");
		return -1;
	}

	wrote = sdcard_write(fh, data, length);
	if (wrote != length) {
		printf("Did not write full .bmp file: wrote <%d> of <%d> bytes\n", wrote, length);
		return -1;
	}

	if (sdcard_close(fh) != 0) {
		printf("Could not close SDCard file\n");
		return -1;
	}

	return 0;
}

int bitmap_process_header(const char * header, int * imagefilesize, int * data_start_offset, int * width, int * height) {

	/* Check the magic numbers at the start of our file to make sure this is a .bmp file */
	if ((0xFF & header[0]) != 0x42 || (0xFF & header[1]) != 0x4D) {
		printf("Error: Not a .bmp file\n");
		return -1;
	}

	/*
	 * The bitmap size if stored as
	 * 	high bits:	bytes 2, 3
	 * 	low bits:	bytes 4, 5
	 */
	/* Low bits */
	*imagefilesize = 0x0000FFFF & ((header[3] << 8) + (0xFF & header[2]));
	/* High bits */
	*imagefilesize += 0xFFFF0000 & ((header[5] << 24) + (header[4] << 16));

	/* Process the header to find the offset where the bitmap data resides */
	/*
	 * The bitmap data offset is stored as:
	 * 	high bits:	bytes 10, 11
	 * 	low bits:	bytes 12, 13
	 */
	/* Low bits */
	*data_start_offset = 0x0000FFFF & ((header[11] << 8) + (0xFF & header[10]));
	/* High bits */
	*data_start_offset += 0xFFFF0000 & ((header[13] << 24) + (header[12] << 16));

	/* Process the header to find the width and height */
	/*
	 * The bitmap data offset is stored as:
	 * 	width bits:		bytes 18-21
	 * 	height bits:	bytes 22-25
	 */
	*width = 0x0000FFFF & ((header[19] << 8) + (0xFF & header[18]));
	*width += 0xFFFF0000 & ((header[21] << 24) + (header[20] << 16));
	*height = 0x0000FFFF & ((header[23] << 8) + (0xFF & header[22]));
	*height += 0xFFFF0000 & ((header[25] << 24) + (header[24] << 16));

	return 0;
}

int bitmap_draw(const char * bitmap) {
	int result;
	int imagefilesize;
	int bitmap_data_offset;
	int width;
	int height;
	int i;

	int x = 0;
	int y = 0;
	bitmap_rgb_t rgb;

	result = bitmap_process_header(bitmap, &imagefilesize, &bitmap_data_offset, &width, &height);
	if (result != 0) {
		return result;
	}

	graphics_clear_screen();

	i = bitmap_data_offset;
	/* Gotta draw the picture backwards to make it display upright on the VGA */
	for (y = height - 1; y >= 0; y--) {
		for (x = 0; x < width; x++) {
			rgb.b = 0x000000FF & (bitmap[i]);
			i++;
			rgb.g = 0x000000FF & (bitmap[i]);
			i++;
			rgb.r = 0x000000FF & (bitmap[i]);
			i++;

			/* Make sure we are only drawing what fits on the screen */
			if (x < GRAPHICS_PIXEL_WIDTH && y < GRAPHICS_PIXEL_HEIGHT)
				graphics_write_pixel(x + 20, y + 20, rgb_to_8bit(rgb.r, rgb.g, rgb.b));
		}
	}

	return 0;
}

static int bitmap_draw_scaled(const char * bitmap, const int scaled_width, const int scaled_height, const int origin_x, const int origin_y) {
	int result;
	int imagefilesize;
	int bitmap_data_offset;
	int width;
	int height;
	int i;

	int x = 0;
	int y = 0;
	int allocated_y = 0;
	bitmap_rgb_t ** rgb;
	bitmap_rgb_t scaled_rgb;
	float x_scale;
	float y_scale;

	int x_coord;
	int y_coord;

	result = bitmap_process_header(bitmap, &imagefilesize, &bitmap_data_offset, &width, &height);
	if (result != 0) {
		return result;
	}

	graphics_clear_screen();

	i = bitmap_data_offset;
	/* Import the RGB values into our array */
	rgb = malloc(sizeof(bitmap_rgb_t *) * height);
	if (rgb == NULL) {
		printf("Out of memory\n");
		return -1;
	}
	for (y = height - 1; y >= 0; y--) {
		rgb[y] = malloc(sizeof(bitmap_rgb_t) * width);
		if (rgb[y] == NULL) {
			printf("Out of memory\n");
			allocated_y = y;
			result = -1;
			goto done;
		}

		for (x = 0; x < width; x++) {
			rgb[y][x].b = 0x000000FF & (bitmap[i]);
			i++;
			rgb[y][x].g = 0x000000FF & (bitmap[i]);
			i++;
			rgb[y][x].r = 0x000000FF & (bitmap[i]);
			i++;
		}
	}

	/* Determine our scaling factors */
	x_scale = (float)scaled_width / width;
	y_scale = (float)scaled_height / height;

	/* Bitmaps are stored left to right, bottom row to top row */
	for (y = scaled_height - 1; y >= 0; y--) {
		for (x = 0; x < scaled_width; x++) {
			x_coord = x / x_scale;
			y_coord = y / y_scale;

			scaled_rgb = rgb[y_coord][x_coord];
			/* Make sure we are only drawing what fits on the screen */
			if (x + origin_x < GRAPHICS_PIXEL_WIDTH &&
					y + origin_y < GRAPHICS_PIXEL_HEIGHT &&
					x + origin_x >= 0 &&
					y + origin_y >= 0)
				graphics_write_pixel(x + origin_x, y + origin_y, rgb_to_8bit(scaled_rgb.r, scaled_rgb.g, scaled_rgb.b));
		}
	}

	result = 0;

done:
	for (y = height - 1; y >= allocated_y; y--) {
		free(rgb[y]);
	}
	free(rgb);

	return result;
}

int bitmap_draw_centered_fullscreen(const char * bitmap) {
	int result;
	int imagefilesize;
	int bitmap_data_offset;
	int width;
	int height;

	float x_scale;
	float y_scale;

	int x_origin;
	int y_origin;

	result = bitmap_process_header(bitmap, &imagefilesize, &bitmap_data_offset, &width, &height);
	if (result != 0) {
		return result;
	}

	/* Calculate the scaling factors */
	x_scale = (float)GRAPHICS_PIXEL_WIDTH / width;
	y_scale = (float)GRAPHICS_PIXEL_HEIGHT / height;

	/* We have to pick the smaller factor to use */
	if (x_scale < y_scale) {
		width = GRAPHICS_PIXEL_WIDTH - 1;
		height = (height * x_scale) - 1;
	} else {
		width = (width * y_scale) - 1;
		height = GRAPHICS_PIXEL_HEIGHT - 1;
	}

	/* Determine a starting origin for our image */
	x_origin = ((GRAPHICS_PIXEL_WIDTH - width) / 2) + 1;
	y_origin = ((GRAPHICS_PIXEL_HEIGHT - height) / 2) + 1;

	return bitmap_draw_scaled(bitmap, width, height, x_origin, y_origin);
}
