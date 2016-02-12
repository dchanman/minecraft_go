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

	savefile_save(data_orig);
	savefile_load(&data_loaded);

	if (data_orig.creeps_defeated != data_loaded.creeps_defeated)
		printf("creeps_defeated: expected <%d>, actual <%d>\n", data_orig.creeps_defeated, data_loaded.creeps_defeated);

	if (data_orig.health != data_loaded.health)
		printf("health: expected <%d>, actual <%d>\n", data_orig.health, data_loaded.health);

	printf("Done!\n");
}
