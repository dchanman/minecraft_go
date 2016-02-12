#include <stdio.h>
#include <string.h>
#include <altera_up_sd_card_avalon_interface.h>
#include "sdcard.h"

void sdcard_test() {
	short int filehandle;
	const char * msg = "CPEN391 MINECRAFT GO\n";
	const char * msg2 = "This is a test\n";

	sdcard_init();
	sdcard_open(&filehandle, "hello1.txt");
	sdcard_write(filehandle, msg, strlen(msg));
	sdcard_write(filehandle, msg2, strlen(msg2));
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
