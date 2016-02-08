#include <stdint.h>
#include <stdio.h>

/* Comment this #define out when we're done testing */
#define TESTING

#ifdef TESTING
#include "test.h"
#endif

int main() {
	printf("Minecraft GO\n");

	/* Uncomment the feature you want to test */
	//rs232_test_multi_char();
	//rs232_test_single_char();
	//sdcard_test_open();
	//sdcard_test();
	//gps_test();
	//minecraft_rpc_test_main();
	//minecraft_rpc_test_protocol_msg();
	bluetooth_test();
	//touchscreen_test();
	//sprint1_demo();

	return 0;
}


