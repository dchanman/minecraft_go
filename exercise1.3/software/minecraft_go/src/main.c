#include <stdint.h>
#include <stdio.h>

/* Comment this #define out when we're done testing */
#define TESTING

#ifdef TESTING
#include "rs232_test.h"
#include "general.h"
#endif

int main() {
	printf("Minecraft GO\n");

	/* Uncomment the feature you want to test */
	//rs232_test_multi_char();
	//rs232_test_single_char();
	GPS_test();

	printf("DONE\n");
	return 0;
}




