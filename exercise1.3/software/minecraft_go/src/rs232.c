/*
 * rs232.c
 *
 *  Created on: Jan 14, 2016
 *      Author: derek
 */

#include "general.h"
#include "rs232.h"
#include "serial.h"

#define RS232	((volatile unsigned char *)(0x84000200))

void rs232_init() {
	serial_init(RS232, BAUD_RATE_115K);
}

void rs232_put_char(const unsigned char c) {
	serial_put_char(RS232, c);
}

void rs232_put_n_char(const unsigned char * msg, const int msg_length) {
	serial_put_n_char(RS232, msg, msg_length);
}

unsigned char rs232_get_char() {
	return serial_get_char(RS232);
}

void rs232_get_n_char(unsigned char * recv_msg, const int recv_msg_length) {
	return serial_get_n_char(RS232, recv_msg, recv_msg_length);
}

int rs232_test_for_received_data() {
	return serial_test_for_received_data(RS232);
}
