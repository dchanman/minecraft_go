/*
 * picture_transfer_test.c
 *
 *  Created on: Mar 29, 2016
 *      Author: Logan
 */

//test receiving message
//#define RECEIVING_TESTING

//test sending message
#define SENDING_TESTING

#include <stdint.h>
#include <stdio.h>
#include "picture_transfer.h"

void picture_transfer_test() {
	picture_transfer_init();

	#ifdef RECEIVING_TESTING
		unsigned char * recv_msg = NULL;
		memset(recv_msg, '\0', sizeof(recv_msg));
		picture_transfer_receive(recv_msg);
	#endif

	#ifdef SENDING_TESTING
		const unsigned char *filename = "test.bmp";
		picture_transfer_send(filename);
	#endif

	usleep(1000000);
	printf("End of test!\n");
}
