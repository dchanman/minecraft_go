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
 * Note that opening a file will open it to the BEGINNING of the file, and
 * writing any data will overwrite any existing data
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
int sdcard_close(short int filehandle);

/**
 * Writes to the opened file on the sdcard
 *
 * @param filehandle - an open filehandle
 * @param data - data to write to the file
 * @param data_length - length of the data
 */
int sdcard_write(const short int filehandle, const char * buffer, const int buffer_length);

/**
 * Writes a buffer terminated with \n to the sdcard
 *
 * @param filehandle - an open filehandle
 * @param data - data to write to the file
 * @param data_length = length of the data
 */
int sdcard_writeln(const short int filehandle, const char * data, const int data_length);

/**
 * Reads a string from an opened file on the sdcard.
 * Automatically null terminates the buffer provided.
 *
 * @param filehandle - an open filehandle
 * @param buffer - buffer to store the read data
 * @param num - amount to read into the buffer
 * @returns - number of bytes read from file
 */
int sdcard_readstr(const short int filehandle, char * buffer, const int num);

/**
 * Reads from an opened file on the sdcard
 *
 * @param filehandle - an open filehandle
 * @param buffer - buffer to store the read data
 * @param num - amount to read into the buffer
 * @returns - number of bytes read from file
 */
int sdcard_read(const short int filehandle, char * buffer, const int num);

/**
 * Reads a line from an opened file on the sdcard
 *
 * @param filehandle - an open filehandle
 * @param buffer - buffer to store the read data
 * @param buffer_size - the max number of bytes to read into the buffer
 * @returns - number of bytes read from file
 */
int sdcard_readln(const short int filehandle, char * buffer, const int buffer_size);

/**
 * Gets a list of files from a directory on the sdcard
 *
 * Note that filelist's indices will point to allocated memory that needs to be freed
 * when no longer needed.
 *
 * @param[inout] filelist - list of file names
 * @param[out] numfiles - number of files
 * @param[in] directory - directory to search
 */
int sdcard_get_files(char ** filelist, int * numfiles, const char * directory);

#endif /* SDCARD_H_ */
