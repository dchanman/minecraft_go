/*
 * savefile.c
 *
 *  Created on: Feb 11, 2016
 *      Author: derek
 */

#include "sdcard.h"
#include "stdlib.h"
#include "string.h"
#include "savefile.h"

#define SAVEFILE_NAME	"mc_go.txt"
#define SAVEFILE_BUFFER_SIZE	16

void savefile_init()
{
	sdcard_init();
}

boolean savefile_load(savedata_t * data)
{
	short int fd;
	int result;
	char buffer[SAVEFILE_BUFFER_SIZE];

	result = sdcard_open(&fd, SAVEFILE_NAME);
	if (result != 0) {
		printf("savefile_load: Error opening sdcard\n");
		return FALSE;
	}

	/* Read data back into the buffer in alphabetical order */
	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->creeps_defeated = atoi(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->health = atoi(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->destination.lat_degree = atoi(buffer);

	/* Location */
	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->destination.lat_minute = atof(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->destination.lat_direction = buffer[0];

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->destination.long_degree = atoi(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->destination.long_minute = atof(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->destination.long_direction = buffer[0];

	/* DateTime */

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->start_time.year = atoi(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->start_time.month = atoi(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->start_time.day = atoi(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->start_time.hour = atoi(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->start_time.minute = atoi(buffer);

	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->start_time.second = atoi(buffer);

	/* Other flags */
	result = sdcard_readln(fd, buffer, sizeof(buffer));
	if (result < 0)
		goto error;
	data->journey_complete = atoi(buffer);


	sdcard_close(fd);
	return TRUE;

error:
	printf("savefile_load: Error reading from sdcard\n");
	sdcard_close(fd);
	return FALSE;

}


boolean savefile_save(const savedata_t data)
{
	short int fd;
	int result;
	char buffer[SAVEFILE_BUFFER_SIZE];

	result = sdcard_open(&fd, SAVEFILE_NAME);
	if (result != 0) {
		printf("savefile_save: Error opening sdcard\n");
		return FALSE;
	}


	/* Write data in struct order */
	snprintf(buffer, sizeof(buffer), "%d", data.creeps_defeated);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%d", data.health);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	/* Location */
	snprintf(buffer, sizeof(buffer), "%d", data.destination.lat_degree);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%.3lf", data.destination.lat_minute);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%c", data.destination.lat_direction);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%d", data.destination.long_degree);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%.3lf", data.destination.long_minute);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%c", data.destination.long_direction);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	/* DateTime */

	snprintf(buffer, sizeof(buffer), "%d", data.start_time.year);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%d", data.start_time.month);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%d", data.start_time.day);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%d", data.start_time.hour);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%d", data.start_time.minute);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%d", data.start_time.second);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	snprintf(buffer, sizeof(buffer), "%d", data.journey_complete);
	result = sdcard_writeln(fd, buffer, strlen(buffer));
	if (result != 0)
		goto error;

	sdcard_close(fd);

	return TRUE;

error:
	printf("savefile_save: Error writing to sdcard\n");
	sdcard_close(fd);
	return FALSE;
}

