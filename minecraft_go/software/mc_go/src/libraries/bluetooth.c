/*
 * bluetooth.c
 *
 *  Created on: 2016-01-25
 *      Author: Johnson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "general.h"
#include "serial.h"
#include "bluetooth.h"

#define BLUETOOTH ((volatile unsigned char *)(0x84000220))


void bluetooth_init() {
	//serial_init(BLUETOOTH, BAUD_RATE_115K);

	*BLUETOOTH = 0x15; // 0b00010101
	*(BLUETOOTH + 4) = 0x01;
}

void bluetooth_put_char(const unsigned char c) {
	serial_put_char(BLUETOOTH, c);
}

unsigned char bluetooth_get_char() {
	usleep(1000);
	return serial_get_char(BLUETOOTH);
}

void bluetooth_get_n_char(unsigned char *recv_msg, const int recv_msg_length) {
	usleep(1000000);
	serial_get_n_char(BLUETOOTH, recv_msg, recv_msg_length);
}

void bluetooth_send_command(const unsigned char *command){
	usleep(3000); // no handshaking for bluetooth so sleep 1 second
	int i;
	for (i = 0; i < strlen(command); i++) {
		bluetooth_put_char(command[i]);
		//printf("Char send: %c\n", command[i]);
		usleep(1000);
	}

	usleep(3000); // no handshaking for bluetooth so sleep 1 second
	//printf("\n");
}

void bluetooth_send_data(const unsigned char *command, const int length){
	usleep(3000); // no handshaking for bluetooth so sleep 1 second
	int i;
	for (i = 0; i < length; i++) {
		bluetooth_put_char(command[i]);
		//printf("Char send: %c\n", command[i]);
		usleep(1000);
	}

	usleep(3000); // no handshaking for bluetooth so sleep 1 second
	//printf("\n");
}

int bluetooth_send_cmd_from_template(const char *cmd_template, const char *value){
	//error checking
	if (strcmp(cmd_template, BLUETOOTH_SET_NAME_TEMPLATE) == 0){
		if (strlen(value) > 20){
			printf("Name change failed: name is too long (>20 chars)\n");
			return 0;
		}
	} else if (strcmp(cmd_template, BLUETOOTH_SET_PIN_TEMPLATE) == 0){
		if (strlen(value) > 4){
			printf("Pin change failed: pin is too long (>4 digits)\n");
			return 0;
		}
	}

	char *command = malloc(50 * sizeof(char));

	sprintf(command, cmd_template, value);
	bluetooth_send_command(command);

	free(command);

	return 1;
}


/*
// name -  a string up to 20 alphanumeric characters
int bluetooth_change_name(const char *name){
	if (strlen(name) > 20) {
			printf("Name change failed: name is too long (>20 chars)\n");
			return 0;
	}
	char *command = malloc(50 * sizeof(char));
	sprintf(command, SET_NAME_TEMPLATE, name);
	bluetooth_send_command(command);
	free(command);
	return 1;
}
// pin -  a 4 digit integer (ie. 1234)
int bluetooth_change_pin(unsigned int pin){
	if (pin > 9999) {
		printf("Pin change failed: pin is too long (>4 digits)\n");
		return 0;
	}
	char *command = malloc(50 * sizeof(char));
	sprintf(command, SET_PIN_TEMPLATE, pin);
	bluetooth_send_command(command);
	free(command);
	return 1;
}
void bluetooth_fact_reset(){
	bluetooth_send_command(FACTORY_RESET);
}
*/

void bluetooth_echo_back_data(){
	char curr_char = bluetooth_get_char();
	while (!isspace(curr_char))
		printf("%c", curr_char);

	printf("\n");
}
