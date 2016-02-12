/*
 * sdcard.c
 *
 *  Created on: Jan 21, 2016
 *      Author: derek
 */

#include <stdio.h>
#include "sdcard.h"
#include <altera_up_sd_card_avalon_interface.h>

#define SDCARD_DEV "/dev/altera_up_sd_card_avalon_interface_0"

static alt_up_sd_card_dev *device_reference = NULL;

int sdcard_init() {
	printf("Opening SDCard\n");
	device_reference = alt_up_sd_card_open_dev(SDCARD_DEV);
	if (device_reference == NULL) {
		printf("Error: Could not open SDCard\n");
		return 1;
	}

	printf("Opened SDCard\n");
	return 0;
}

int sdcard_open(short int * filehandle, char * filename)
{
	if (device_reference == NULL) {
		printf("Error: SDCard not open\n");
		return 1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("Error: SDCard not present\n");
		device_reference = NULL;
		return 1;
	}

	if (!alt_up_sd_card_is_FAT16()) {
		printf("Error: SDCard is not FAT16 format\n");
		return 1;
	}

	/* Try to create the file */
	*filehandle = alt_up_sd_card_fopen(filename, true);
	if (*filehandle == -1) {
		printf("Info: Could not create file <%s>, trying to open file instead...\n", filename);

		/* Maybe the file exists, try opening it instead */
		*filehandle = alt_up_sd_card_fopen(filename, false);
		if (*filehandle == -1) {
			printf("Error: Could not open file <%s>\n", filename);
			return 1;
		} else {
			printf("Opened file <%s>\n", filename);
		}
	} else {
		printf("Created file <%s>\n", filename);
	}

	return 0;
}

int sdcard_close(short int filehandle)
{
	if (device_reference == NULL) {
		printf("Error: SDCard not open\n");
		return 1;
	}

	if (filehandle == -1) {
		printf("Error: File handle not open\n");
		return 1;
	}

	if (!alt_up_sd_card_fclose(filehandle)) {
		printf("Error: Could not close filehandle\n");
		return 1;
	}

	printf("Closed SDCard file\n");

	return 0;
}

int sdcard_write(const short int filehandle, const char * data, const int data_length)
{
	int i;

	if (device_reference == NULL) {
		printf("Error: SDCard not open\n");
		return 1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("Error: SDCard not present\n");
		device_reference = NULL;
		return 1;
	}

	if (filehandle == -1) {
		printf("Error: File handle not open\n");
		return 1;
	}

	/* Write data to the SDCard */
	for (i = 0; i < data_length; i++) {
		if (alt_up_sd_card_write(filehandle, data[i]) == false) {
			printf("Error: Could not write to file. Aborting write\n");
			break;
		}
	}

	return 0;
}

int sdcard_writeln(const short int filehandle, const char * data, const int data_length)
{
	int result = sdcard_write(filehandle, data, data_length);
	if (result != 0)
		return result;

	result = sdcard_write(filehandle, "\n", 1);
	return result;
}

int sdcard_read(const short int filehandle, char * buffer, const int num)
{
	int i;

	if (device_reference == NULL) {
		printf("Error: SDCard not open\n");
		return 1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("Error: SDCard not present\n");
		device_reference = NULL;
		return 1;
	}

	if (filehandle == -1) {
		printf("Error: File handle not open\n");
		return 1;
	}

	/* Read data from the SDCard */
	for (i = 0; i < num - 1; i++) {
		buffer[i] = (char)alt_up_sd_card_read(filehandle);
		if (buffer[i] == -1) {
			printf("Error: File handle was invalid\n");
			return 1;
		}

		if (buffer[i] == -2) {
			printf("Error: Unable to read from SD Card\n");
			return 1;
		}

		if (buffer[i] == '\0') {
			break;
		}
	}
	buffer[i] = '\0';

	return i;
}

int sdcard_readln(const short int filehandle, char * buffer, const int buffer_size)
{
	int i = 0;

	if (device_reference == NULL) {
		printf("Error: SDCard not open\n");
		return 1;
	}

	if (!alt_up_sd_card_is_Present()) {
		printf("Error: SDCard not present\n");
		device_reference = NULL;
		return 1;
	}

	if (filehandle == -1) {
		printf("Error: File handle not open\n");
		return 1;
	}

	/* Read data from the SDCard */
	for (i = 0; i < buffer_size; i++) {
		buffer[i] = (char)alt_up_sd_card_read(filehandle);
		if (buffer[i] == -1) {
			printf("Error: File handle was invalid\n");
			return 1;
		}

		if (buffer[i] == -2) {
			printf("Error: Unable to read from SD Card\n");
			return 1;
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
