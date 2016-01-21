/*
 * sdcard.h
 *
 *  Created on: Jan 21, 2016
 *      Author: derek
 */

#ifndef SDCARD_H_
#define SDCARD_H_

/**
 * sdcard_init() must be called before running any other sdcard operation
 */
int sdcard_init();

/**
 * Opens a file on the sdcard for reading or writing.
 *
 * IMPORTANT: Be sure to close your file when you're done!
 *
 * @param filehandle
 * @param filename - the name of the file to be opened
 */
int sdcard_open(short int * filehandle, char * filename);

/**
 * Closes the opened file on sdcard
 *
 * @param filehandle - an open filehandle
 */
int sdcard_close(short int * filehandle);

/**
 * Writes to the opened file on the sdcard
 *
 * @param filehandle - an open filehandle
 * @data - data to write to the file
 * @data_length - length of the data
 */
int sdcard_write(const short int * filehandle, const char * data, const int data_length);

#endif /* SDCARD_H_ */
