/*
 * bitmap.h
 *
 *  Created on: Mar 17, 2016
 *      Author: derek
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#define STEGO_ENGINE_BMP_HEADER_SIZE 14

/**
 * Imports a bitmap image from the SD card.
 * On success, data_out points to an allocated char buffer containing the bitmap data.
 *
 * data_out needs to be free'd when finished.
 *
 * @param[in] filename
 * @param[out] data_out - char array containing the bitmap data
 * @param[out] length - size of data_out
 * @param[out] data_start_offset - the index in data_out where RGB data begins
 * @return 0 on success, -1 on error
 */
int bitmap_import_image(const char *filename, char **data_out, int * length, int * data_start_offset);

/**
 * Exports a bitmap image to the SD card.
 *
 * @bug cannot export files larger than 65536 bytes.
 *
 * @param[in] filename
 * @param[in] data - char array containing the bitmap data
 * @param[in] length - the length of the bitmap data
 * @return 0 on success, -1 on error
 */
int bitmap_export_image(const char * filename, const char * data, const int length);

/**
 * Extracts information from a bitmap file's header.
 *
 * @param[in] header - char array containing a bitmap header
 * @param[out] imagefilesize - size of the entire bitmap file
 * @param[out] data_start_offset - byte offset indicating where the bitmap RGB data begins
 * @param[out] width - width of bitmap
 * @param[out]height - height of bitmap
 * @return 0 on success, -1 on error
 */
int bitmap_process_header(const char * header, int * imagefilesize, int * data_start_offset, int * width, int * height);

/**
 * Draws a bitmap over VGA
 *
 * This function processes the bitmap header. You only need to pass in the
 * char array data_out from bitmap_import_image.
 *
 * @param[in] bitmap - data from bitmap_import_image
 * @return 0 on success, -1 on error
 */
int bitmap_draw(const char * bitmap);

/**
 * Draws a bitmap to the VGA. The dimensions will be scaled to fill the screen
 * and the image will be centered.
 *
 * This function processes the bitmap header. You only need to pass in the
 * char array data_out from bitmap_import_image.
 *
 * @param[in] bitmap - data from bitmap_import_image
 * @return 0 on success, -1 on error
 */
int bitmap_draw_centered_fullscreen(const char * bitmap);

#endif /* BITMAP_H_ */
