/*
 * bluetooth_test.c
 *
 *  Created on: 2016-01-25
 *      Author: Johnson
 */

#include <stdint.h>
#include <stdio.h>
#include "bluetooth.h"

void getAndPrintACK(){
	char ack = bluetooth_get_char();
	printf("ACK received: %c\n", ack);
}

void bluetooth_test() {
	// use the bluetooth default for now
	bluetooth_init();


	usleep(1500000);
	bluetooth_send_command(BLUETOOTH_CMD_MODE); // go into command mode for bluetooth

	usleep(1500000);
	//bluetooth_send_command(BLUETOOTH_FACTORY_RESET);

	/*
	bluetooth_send_command("D\r\n");

	int i;
	for (i = 0; i < 100; i++){
		char ack = bluetooth_get_char();
		printf("%c", ack);
	}*/



	if (bluetooth_send_cmd_from_template(BLUETOOTH_SET_NAME_TEMPLATE, BLUETOOTH_NAME)){
		getAndPrintACK();
		getAndPrintACK();
		printf("Set name success!\n");
	}
	else
		printf("Set name failed!\n");


	/*
	if (bluetooth_send_cmd_from_template(BLUETOOTH_SET_PIN_TEMPLATE, BLUETOOTH_PIN))
		printf("Set pin success!\n");
	else
		printf("Set pin failed!\n");
	*/

	bluetooth_send_command(BLUETOOTH_CMD_MODE_EXIT);

	printf("Bluetooth test done.\n");
}
