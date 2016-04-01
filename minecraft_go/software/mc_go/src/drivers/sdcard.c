/*
 * sdcard.c
 *
 *  Created on: Jan 21, 2016
 *      Author: derek
 */

#include <stdio.h>
#include <string.h>
#include "sdcard.h"
#include <altera_up_sd_card_avalon_interface.h>

#define SDCARD_DEV "/dev/altera_up_sd_card_avalon_interface_0"

static alt_up_sd_card_dev *device_reference = NULL;

int sdcard_init() {
	printf("[%s]: Opening SDCard\n", __func__);
	device_reference = alt_up_sd_card_open_dev(SDCARD_DEV);
	if (device_reference == NULL) {
		printf("[%s]: Error: Could not open SDCard\n", __func__);
		return -1;
	}

	printf("[%s]: Opened SDCard\n", __func__);
	return 0;
}

int sdcard_open(short int * filehandle, char * filename)
{
	if (device_reference == NULL) {
		printf("[%s]: Error: SDCard not open\n", __func__);
		return -1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("[%s]: Error: SDCard not present\n", __func__);
		device_reference = NULL;
		return -1;
	}

	if (!alt_up_sd_card_is_FAT16()) {
		printf("[%s]: Error: SDCard is not FAT16 format\n", __func__);
		return -1;
	}

	/* Try to create the file */
	*filehandle = alt_up_sd_card_fopen(filename, true);
	if (*filehandle == -1) {
		//printf("[%s]: Info: Could not create file <%s>, trying to open file instead...\n", __func__, filename);

		/* Maybe the file exists, try opening it instead */
		*filehandle = alt_up_sd_card_fopen(filename, false);
		if (*filehandle == -1) {
			printf("[%s]: Error: Could not open file <%s>\n", __func__, filename);
			return -1;
		} else {
			//printf("[%s]: Opened file <%s>\n", __func__, filename);
		}
	} else {
		printf("[%s]: Created file <%s>\n", __func__, filename);
	}

	return 0;
}

int sdcard_close(short int filehandle)
{
	if (device_reference == NULL) {
		printf("[%s]: Error: SDCard not open\n", __func__);
		return -1;
	}

	if (filehandle == -1) {
		printf("[%s]: Error: File handle not open\n", __func__);
		return -1;
	}

	if (!alt_up_sd_card_fclose(filehandle)) {
		printf("[%s]: Error: Could not close filehandle\n", __func__);
		return -1;
	}

	//printf("[%s]: Closed SDCard file\n", __func__);

	return 0;
}

int sdcard_write(const short int filehandle, const char * data, const int data_length)
{
	int i;

	if (device_reference == NULL) {
		printf("[%s]: Error: SDCard not open\n", __func__);
		return -1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("[%s]: Error: SDCard not present\n", __func__);
		device_reference = NULL;
		return -1;
	}

	if (filehandle == -1) {
		printf("[%s]: Error: File handle not open\n", __func__);
		return -1;
	}

	/* Write data to the SDCard */
	for (i = 0; i < data_length; i++) {
		//if (i % 0x0000FFFF == 0)
		//	printf("[%s]: %08X: %02X\n", __func__, i, data[i]);
		if (alt_up_sd_card_write(filehandle, data[i]) == false) {
			printf("[%s]: Error: Could not write to file. Aborting write\n", __func__);
			break;
		}
	}
	printf("[%s]: Finished writing %d bytes (%08X)\n", __func__, i, i);

	return i;
}

int sdcard_writeln(const short int filehandle, const char * data, const int data_length)
{
	int result = sdcard_write(filehandle, data, data_length);
	if (result < 0)
		return result;

	result += sdcard_write(filehandle, "\n", 1);
	return result;
}

int sdcard_readstr(const short int filehandle, char * buffer, const int num)
{
	int i = -1;

	if (device_reference == NULL) {
		printf("[%s]: Error: SDCard not open\n", __func__);
		return -1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("[%s]: Error: SDCard not present\n", __func__);
		device_reference = NULL;
		return -1;
	}

	if (filehandle == -1) {
		printf("[%s]: Error: File handle not open\n", __func__);
		return -1;
	}

	/* Read data from the SDCard */
	for (i = 0; i < num; i++) {
		buffer[i] = (char)alt_up_sd_card_read(filehandle);
		if (buffer[i] == -1) {
			printf("[%s]: Error: File handle was invalid\n", __func__);
			return -1;
		}

		if (buffer[i] == -2) {
			printf("[%s]: Error: Unable to read from SD Card\n", __func__);
			return -1;
		}

		if (buffer[i] == '\0') {
			break;
		}
	}
	buffer[i] = '\0';

	return i;
}

int sdcard_read(const short int filehandle, char * buffer, const int num)
{
	int i = -1;
	short int result;

	if (device_reference == NULL) {
		printf("[%s]: Error: SDCard not open\n", __func__);
		return -1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("[%s]: Error: SDCard not present\n", __func__);
		device_reference = NULL;
		return -1;
	}

	if (filehandle == -1) {
		printf("[%s]: Error: File handle not open\n", __func__);
		return -1;
	}

	/* Read data from the SDCard */
	for (i = 0; i < num; i++) {
		result = alt_up_sd_card_read(filehandle);
		if (result == -1) {
			printf("[%s]: Error: File handle was invalid on read <%d> (%08X)\n", __func__, i, i);
			return -1;
		}

		if (result == -2) {
			printf("[%s]: Error: Unable to read from SD Card\n", __func__);
			return -1;
		}
		buffer[i] = (char)result;
	}

	return i;
}

int sdcard_readln(const short int filehandle, char * buffer, const int buffer_size)
{
	int i = 0;

	if (device_reference == NULL) {
		printf("[%s]: Error: SDCard not open\n", __func__);
		return -1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("[%s]: Error: SDCard not present\n", __func__);
		device_reference = NULL;
		return -1;
	}

	if (filehandle == -1) {
		printf("[%s]: Error: File handle not open\n", __func__);
		return -1;
	}

	/* Read data from the SDCard */
	for (i = 0; i < buffer_size; i++) {
		buffer[i] = (char)alt_up_sd_card_read(filehandle);
		if (buffer[i] == -1) {
			printf("[%s]: Error: File handle was invalid\n", __func__);
			return -1;
		}

		if (buffer[i] == -2) {
			printf("[%s]: Error: Unable to read from SD Card\n", __func__);
			return -1;
		}

		/* Read until the newline */
		if (buffer[i] == '\n') {
			break;
		}

		if (buffer[i] == '\0') {
			break;
		}
	}
	buffer[i] = '\0';

	return i;
}

int sdcard_get_files(char ** filelist, int * numfiles, const char * directory) {
	int i = 0;
	bool fat16;
	short int result;
	char buffer[13];

	char dir[32];
	strcpy(dir, directory);

	/**
	 *  The SDCard module is buggy as hell. You need to call this function
	 *  to set the internal FAT16 flag. Otherwise, alt_up_sd_card_find_first
	 *  will always fail.
	 */
	fat16 = alt_up_sd_card_is_FAT16();

	*numfiles = 0;
	result = alt_up_sd_card_find_first(dir, buffer);

	while (result == 0) {
		/*
		 * The SDCard module seriously sucks. It returns a truckload of trash.
		 * Seriously, Altera. Did you get a bunch of Co-ops to write this in version 13.1?
		 *
		 * I've spent too much time digging around forums. The best thing I could do here
		 * is filter out the trash. Sorry guys.
		 *
		 * Trash filenames don't contain file extensions.
		 * Examples of trash:
		 * 	* AO
		 * 	* (null)
		 * 	* Af
		 *
		 * By filtering filenames to the ones that contain '.' characters, we get rid of trash.
		 */
		if (strstr(buffer, ".") != NULL) {
			filelist[*numfiles] = strdup(buffer);
			(*numfiles)++;
		}

		i++;
		result = alt_up_sd_card_find_next(buffer);
	}

	return 0;

}
