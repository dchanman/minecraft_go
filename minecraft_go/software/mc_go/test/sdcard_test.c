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
	data_orig.destination.lat_degree = 0.921;
	data_orig.destination.lat_direction= 'E';
	data_orig.destination.lat_minute = 1;
	data_orig.destination.long_degree = 1.289;
	data_orig.destination.long_minute = 4;
	data_orig.destination.long_direction = 'W';

	savefile_save(data_orig);
	savefile_load(&data_loaded);

	if (data_orig.creeps_defeated != data_loaded.creeps_defeated)
		printf("creeps_defeated: expected <%d>, actual <%d>\n", data_orig.creeps_defeated, data_loaded.creeps_defeated);

	if (data_orig.health != data_loaded.health)
		printf("health: expected <%d>, actual <%d>\n", data_orig.health, data_loaded.health);

	if (data_orig.destination.lat_degree != data_loaded.destination.lat_degree)
			printf("destination.lat_degree: expected <%d>, actual <%d>\n", data_orig.destination.lat_degree, data_loaded.destination.lat_degree);

	if (data_orig.destination.lat_minute != data_loaded.destination.lat_minute)
			printf("destination.lat_minute: expected <%lf>, actual <%lf>\n", data_orig.destination.lat_minute, data_loaded.destination.lat_minute);

	if (data_orig.destination.lat_direction != data_loaded.destination.lat_direction)
			printf("destination.lat_direction: expected <%c>, actual <%c>\n", data_orig.destination.lat_direction, data_loaded.destination.lat_direction);

	if (data_orig.destination.long_degree != data_loaded.destination.long_degree)
			printf("destination.long_degree: expected <%d>, actual <%d>\n", data_orig.destination.long_degree, data_loaded.destination.long_degree);

	if (data_orig.destination.long_minute != data_loaded.destination.long_minute)
			printf("destination.long_minute: expected <%lf>, actual <%lf>\n", data_orig.destination.long_minute, data_loaded.destination.long_minute);

	if (data_orig.destination.long_direction != data_loaded.destination.long_direction)
			printf("destination.long_direction: expected <%c>, actual <%c>\n", data_orig.destination.long_direction, data_loaded.destination.long_direction);

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
