/*
 * minecraft_rpc_test.c
 *
 *  Created on: Jan 23, 2016
 *      Author: derek
 */
#include <stdio.h>
#include "rs232.h"
#include "minecraft_rpc.h"

/**
 * Run this test with the Raspberry Pi Python script:
 * test/rs232_send_and_recv_echo.py
 */
void minecraft_rpc_test_rs232_send_and_recv_echo() {
	rs232_init();

	unsigned char recv;
	while (1) {
		rs232_put_char(recv);
		recv = rs232_get_char();
		printf("%c", recv);
	}
}

/**
 * Run this test with the Raspberry Pi Python script:
 * test/rs232_listen_and_echo.py
 */
void minecraft_rpc_test_protocol_msg() {
	char longitude[10];
	char latitude[11];

	minecraft_rpc_init();
	minecraft_rpc_hi();
	printf("Done hi!\n");
	minecraft_rpc_receive_coordinates(longitude, sizeof(longitude), latitude, sizeof(latitude));
	printf("Done rc!\n");
	minecraft_rpc_journey_complete(1, 2, 3, 4);
	printf("Done jc!\n");
}
