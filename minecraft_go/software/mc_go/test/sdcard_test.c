#include <stdio.h>
#include <string.h>
#include "sdcard.h"
#include "savefile.h"
#include <altera_up_sd_card_avalon_interface.h>


void sdcard_test() {
	short int filehandle;
	const char * msg = "CPEN391 MINECRAFT GO";
	const char * msg2 = "This is a test";

	sdcard_init();
	sdcard_open(&filehandle, "hello1.txt");
	sdcard_writeln(filehandle, msg, strlen(msg));
	sdcard_writeln(filehandle, msg2, strlen(msg2));
	sdcard_close(filehandle);

	char buffer[60];
	memset(buffer, '\0', sizeof(buffer));

	sdcard_open(&filehandle, "hello1.txt");
	int read = sdcard_read(filehandle, buffer, sizeof(buffer) - 1);
	printf("Read: %s\n", buffer);
	printf("Trailing: %x : %c\n", buffer[read], buffer[read]);
	sdcard_close(filehandle);

	sdcard_open(&filehandle, "hello1.txt");
	sdcard_readln(filehandle, buffer, sizeof(buffer) - 1);
	printf("Read: %s\n", buffer);
	sdcard_readln(filehandle, buffer, sizeof(buffer) - 1);
	printf("Read: %s\n", buffer);
	sdcard_close(filehandle);
}

void savefile_test() {
	savedata_t data_orig;
	savedata_t data_loaded;

	savefile_init();

	data_orig.creeps_defeated = 1;
	data_orig.health = 5;
	data_orig.start_time.year = 1;
	data_orig.start_time.month = 2;
	data_orig.start_time.day = 3;
	data_orig.start_time.hour = 4;
	data_orig.start_time.minute = 5;
	data_orig.start_time.second = 6;
	snprintf(data_orig.dest_latitude, sizeof(data_orig.dest_latitude), "1234.1234");
	snprintf(data_orig.dest_longitude, sizeof(data_orig.dest_longitude), "12345.1234");

	savefile_save(data_orig);
	savefile_load(&data_loaded);

	if (data_orig.creeps_defeated != data_loaded.creeps_defeated)
		printf("creeps_defeated: expected <%d>, actual <%d>\n", data_orig.creeps_defeated, data_loaded.creeps_defeated);

	if (data_orig.health != data_loaded.health)
		printf("health: expected <%d>, actual <%d>\n", data_orig.health, data_loaded.health);

	if (strcmp(data_orig.dest_latitude, data_loaded.dest_latitude) != 0)
		printf("dest_latitude: expected <%s>, actual <%s>\n", data_orig.dest_latitude, data_loaded.dest_latitude);

	if (strcmp(data_orig.dest_longitude, data_loaded.dest_longitude) != 0)
		printf("dest_longitude: expected <%s>, actual <%s>\n", data_orig.dest_longitude, data_loaded.dest_longitude);

	if (data_orig.start_time.year != data_loaded.start_time.year)
		printf("start_time.year: expected <%d>, actual <%d>\n", data_orig.start_time.year, data_loaded.start_time.year);

	if (data_orig.start_time.month != data_loaded.start_time.month)
		printf("start_time.month: expected <%d>, actual <%d>\n", data_orig.start_time.month, data_loaded.start_time.month);

	if (data_orig.start_time.day != data_loaded.start_time.day)
		printf("start_time.day: expected <%d>, actual <%d>\n", data_orig.start_time.day, data_loaded.start_time.day);

	if (data_orig.start_time.hour != data_loaded.start_time.hour)
		printf("start_time.hour: expected <%d>, actual <%d>\n", data_orig.start_time.hour, data_loaded.start_time.hour);

	if (data_orig.start_time.minute != data_loaded.start_time.minute)
		printf("start_time.minute: expected <%d>, actual <%d>\n", data_orig.start_time.minute, data_loaded.start_time.minute);

	if (data_orig.start_time.second != data_loaded.start_time.second)
		printf("start_time.second: expected <%d>, actual <%d>\n", data_orig.start_time.second, data_loaded.start_time.second);

	printf("Tests complete!\n");
}
