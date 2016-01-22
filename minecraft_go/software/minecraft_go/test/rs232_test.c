/*
 * rs232_test.c
 *
 *  Created on: Jan 18, 2016
 *      Author: derek
 */

#include <stdint.h>
#include <stdio.h>
#include "rs232.h"

/**
 * Test reading and writing single bytes to the serial port
 */
int rs232_test_single_char() {
	printf("%s\n", __func__);

	rs232_init();

	/* Test program to check communication to Hyperterminal/GtkTerm */
	unsigned char recv;

	while (1) {
		recv = rs232_get_char();
		printf("Received <%c> <0x%x>\n", recv, recv);

		rs232_put_char(recv);
	}

	/* Should not return */
	return 1;
}

/**
 * Test reading and writing multiple bytes to the serial port
 */
int rs232_test_multi_char() {
	printf("%s\n", __func__);

	rs232_init();

	/* Test program to check communication to Hyperterminal/GtkTerm */

	while (1) {
		unsigned char buffer[6] = {'\0'};
		rs232_get_n_char(buffer, sizeof(buffer) - 1);
		printf("Received buffer <%s>\n", buffer);

		rs232_put_n_char(buffer, sizeof(buffer) - 1);
	}

	/* Should not return */
	return 1;
}


