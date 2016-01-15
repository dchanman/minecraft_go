/*
 * rs232.c
 *
 *  Created on: Jan 14, 2016
 *      Author: derek
 */

#include "general.h"
#include "rs232.h"
#include "serial.h"

#define RS232_CONTROL	((volatile unsigned char *)(0x84000200))
#define RS232_STATUS	((volatile unsigned char *)(0x84000200))
#define RS232_TX_DATA	((volatile unsigned char *)(0x84000202))
#define RS232_RX_DATA	((volatile unsigned char *)(0x84000202))
#define RS232_BAUD		((volatile unsigned char *)(0x84000204))

void rs232_init() {
	serial_init(RS232_CONTROL, RS232_BAUD);
}

void rs232_put_char(const unsigned char c) {
	serial_put_char(RS232_STATUS, RS232_TX_DATA, c);
}

unsigned char rs232_get_char() {
	return serial_get_char(RS232_STATUS, RS232_RX_DATA);
}

int rs232_test_for_received_data() {
	return serial_test_for_received_data(RS232_STATUS);
}
