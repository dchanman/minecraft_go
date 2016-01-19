/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "rs232.h"
#include "GPS.h"

int main() {
	printf("Minecraft GO\n");

	GPS_init();

	GPS_send_command(GSP_SNAPSHOT_NOW);

	char * result = GPS_retrive_data_line(1000);

	printf("%s \n",result);

	/*
	rs232_init();

	unsigned char recv;
	while (1) {
		recv = rs232_get_char();
		printf("Received <%c> <0x%x>\n", recv, recv);

		rs232_put_char(recv);
	}
	*/

	return 0;
}


