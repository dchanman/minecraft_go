#include <stdint.h>
#include <stdio.h>

#include "main_controller.h"

/* Comment this #define out when we're done testing */
#define TESTING

#ifdef TESTING
#include "minigames.h"
#include "test.h"
#include "project1_demo.h"
#endif

int main() {
	printf("Minecraft GO\n");

	/* Uncomment the feature you want to test */
	//rs232_test_multi_char();
	//rs232_test_single_char();
	//sdcard_test_open();
	//sdcard_test();
	//gps_test();

	//savefile_test();
	//gps_test();
	//minecraft_rpc_test_main();
	//minecraft_rpc_test_protocol_msg();
	//bluetooth_test();
	//touchscreen_test();
	//touchscreen_test_timeout();
	//sprint1_demo();
	//graphics_test();
	//int health = PLAYER_MAX_HEALTH;
	//minigame_creeper_encounter(&health);
	//minigame_digging();
	//timer_test();

	//project1_demo_initialize_savefile();
	//project1_demo_main();
	//journey_display_test();

	main_controller_run();

	printf("Done\n");

	return 0;
}


