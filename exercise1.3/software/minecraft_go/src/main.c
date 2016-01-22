#include <stdint.h>
#include <stdio.h>

/* Comment this #define out when we're done testing */
#define TESTING

#ifdef TESTING
<<<<<<< HEAD
#include "test.h"
=======
#include "rs232_test.h"
#include "general.h"
>>>>>>> origin/master
#endif

int main() {
	printf("Minecraft GO\n");

	/* Uncomment the feature you want to test */
	//rs232_test_multi_char();
	//rs232_test_single_char();
<<<<<<< HEAD
	//sdcard_test_open();
	sdcard_test();
=======
	GPS_test();
>>>>>>> origin/master

	printf("DONE\n");
	return 0;
}




