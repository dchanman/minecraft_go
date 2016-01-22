/*
 * sdcard.c
 *
 *  Created on: Jan 21, 2016
 *      Author: derek
 */

#include <stdio.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "sdcard.h"

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
		printf("Error: Could not create file <%s>, trying to open file instead...\n", filename);

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

int sdcard_close(short int * filehandle)
{
	if (device_reference == NULL) {
		printf("Error: SDCard not open\n");
		return 1;
	}

	if (*filehandle == -1) {
		printf("Error: File handle not open\n");
		return 1;
	}

	if (!alt_up_sd_card_fclose(*filehandle)) {
		printf("Error: Could not close filehandle\n");
		return 1;
	}

	*filehandle = -1;
	printf("Closed SDCard file\n");

	return 0;
}

int sdcard_write(const short int * filehandle, const char * data, const int data_length)
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

	if (*filehandle == -1) {
		printf("Error: File handle not open\n");
		return 1;
	}

	/* Write data to the SDCard */
	printf("Writing data <%s> length <%d>\n", data, data_length);
	for (i = 0; i < data_length; i++) {
		if (alt_up_sd_card_write(*filehandle, data[i]) == false) {
			printf("Error: Could not write to file. Aborting write\n");
			break;
		}
	}

	return 0;
}
