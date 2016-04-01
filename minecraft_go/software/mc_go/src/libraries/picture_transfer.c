/*
 * picture_transfer.c
 *
 *  Created on: Mar 29, 2016
 *      Author: Logan
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "picture_transfer.h"
#include "bitmap.h"
#include "bluetooth.h"
#include "sdcard.h"

//global variables
static unsigned int recv_msg_length = 0;
static unsigned int actual_msg_length = 0;

//static functions
static void picture_transfer_receive_communication(unsigned char *msg, const int msg_length, const int com_stage);
static void picture_transfer_send_communication(unsigned char *msg, const int length, const int com_stage);

void picture_transfer_init() {
	bluetooth_init();
}

void picture_transfer_receive(unsigned char *recv_msg) {
	unsigned char temp_msg[250];
	memset(temp_msg, '\0', sizeof(temp_msg));

	//check for ready message to start communication
	printf("Waiting for ready message!\n");
	picture_transfer_receive_communication(temp_msg, PICTURE_CONNECTION_CHECK_LENGTH, WAIT);

	//check for length of the string length of the final message
	printf("Waiting for length of string length message!\n");
	picture_transfer_receive_communication(temp_msg, PICTURE_STRING_LENGTH, STRING_LENGTH);

	//check for length of the final message
	printf("Waiting for string length message!\n");
	picture_transfer_receive_communication(temp_msg, recv_msg_length, MESSAGE_LENGTH);

	//check for file
	printf("Waiting for file!\n");
	picture_transfer_receive_communication(recv_msg, actual_msg_length, FINAL);

	//check for offset message
	printf("Waiting for file!\n");
	picture_transfer_receive_communication(recv_msg, actual_msg_length, FINAL);
}

void picture_transfer_send(unsigned char *filename) {
	unsigned char *ready_msg = "S";

	unsigned char length_of_send_msg_length[2];
	memset(length_of_send_msg_length, '\0', sizeof(length_of_send_msg_length));
	unsigned char send_msg_length[10];
	memset(send_msg_length, '\0', sizeof(send_msg_length));

	char * imagedata = NULL;
	int imagelength;
	int offset;
	int result;

	sdcard_init();

	result = bitmap_import_image(filename, &imagedata, &imagelength, &offset);
	if (result != 0) {
		printf("Error with importing image\n");
		return;
	}

	//convert imagelength to string
	snprintf(send_msg_length, sizeof(send_msg_length), "%d", imagelength);

	//get length of send_msg_length
	snprintf(length_of_send_msg_length, sizeof(length_of_send_msg_length), "%d", strlen(send_msg_length));

	//send ready message to start communication
	bluetooth_send_command(ready_msg);
	printf("Ready message sent!\n");

	//send length of the string length of the final message
	picture_transfer_send_communication(length_of_send_msg_length, sizeof(length_of_send_msg_length), STRING_LENGTH);
	printf("Length of string length message sent!\n");

	//send length of the final message
	picture_transfer_send_communication(send_msg_length, sizeof(send_msg_length), MESSAGE_LENGTH);
	printf("String length message sent!\n");

	//send final message
	picture_transfer_send_communication(imagedata, imagelength, FINAL);
	printf("Final message sent!\n");

	free(imagedata);
}

static void picture_transfer_receive_communication(unsigned char *msg, const int msg_length, const int com_stage) {
	int recv_check = 1;
	const unsigned char *ready_check = "R";
	const unsigned char *send_check = "S";
	int i;

	while(recv_check) {
		bluetooth_get_n_char(msg, msg_length);

		switch(com_stage) {
			//wait for ready message
			case WAIT  :
				//compare message received to "R"
				if(strcmp(msg, send_check) == 0) {
					printf("Ready message received!\n\n");
					memset(msg, 0, msg_length);
					bluetooth_send_command(ready_check);
					recv_check = 0;
				}
				break;

			//get length of the string length of the final message
			case STRING_LENGTH  :
				recv_msg_length = atoi(msg);
				//check that recv_msg_length is an integer > 0
				if(recv_msg_length > 0) {
					printf("Length of string length message is %d!\n\n", recv_msg_length);
					memset(msg, 0, msg_length);
					bluetooth_send_command(ready_check);
					recv_check = 0;
				}
				break;

			//get length of the final message
			case MESSAGE_LENGTH  :
				actual_msg_length = atoi(msg);
				//check that recv_msg_length is an integer > 0
				if(actual_msg_length > 0) {
					printf("Length of actual message is %d!\n\n", actual_msg_length);
					memset(msg, 0, msg_length);
					bluetooth_send_command(ready_check);
					recv_check = 0;
				}
				break;

			//get final message
			case FINAL  :
				//check that message received is not NULL
				if(strcmp(msg, "") != 0) {
					printf("Final message received:\n");
					printf("%s\n", msg);
					recv_check = 0;
				}
				break;

			//print an error if com_stage doesn't pass properly
			default :
				printf("ERROR: com_stage not being passed properly!\n");
				recv_check = 0;
				break;
		}
	}
}

static void picture_transfer_send_communication(unsigned char *msg, const int length, const int com_stage) {
	int send_check = 1;
	unsigned char *ready_msg = "R";
	unsigned char ready_check[1];
	memset(ready_check, '\0', PICTURE_CONNECTION_CHECK_LENGTH);

	while(send_check) {
		bluetooth_get_n_char(ready_check, PICTURE_CONNECTION_CHECK_LENGTH);

		//wait for "R" message from receiver
		if(strcmp(ready_check, ready_check) == 0) {
			if(com_stage == FINAL)
				bluetooth_send_data(msg, length);
			else
				bluetooth_send_command(msg);
			send_check = 0;
		}
	}
}
