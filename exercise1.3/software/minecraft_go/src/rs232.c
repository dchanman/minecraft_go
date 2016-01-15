/*
 * rs232.c
 *
 *  Created on: Jan 14, 2016
 *      Author: derek
 */

#include "general.h"
#include "rs232.h"

#define RS232_CONTROL	(*(volatile unsigned char *)(0x84000200))
#define RS232_STATUS	(*(volatile unsigned char *)(0x84000200))
#define RS232_TX_DATA	(*(volatile unsigned char *)(0x84000202))
#define RS232_RX_DATA	(*(volatile unsigned char *)(0x84000202))
#define RS232_BAUD		(*(volatile unsigned char *)(0x84000204))

#define RS232_STATUS_MASK_TX_BIT	(0x02)
#define RS232_STATUS_MASK_RX_BIT	(0x01)

void rs232_init(void) {
	/**
	 * Set up 6850 Control Register to use
	 * * Divide by 16 clock (CR1/CR0 = 01)
	 * * 8-bit data, no parity, 1 stop bit (CR4/CR3/CR2 = 101)
	 * * RTS low, Transmitting Interrupt Disabled (CR6/CR5 = 00)
	 * * Receive Interrupt Enable - Set to 0 arbitrarily (CR7 = 0)
	 *
	 * 0b00010101 = 0x15
	 */
	RS232_CONTROL = 0x15;

	// program baud rate generator to use 115k baud
	RS232_BAUD = 0x01;
}

void rs232_put_char(const unsigned char c) {
	/* Poll Tx bit in 6850 status register. Wait for it to become '1' */
	while ((RS232_STATUS & RS232_STATUS_MASK_TX_BIT) == 0)
		/* Wait */;

	//* Write 'c' to the 6850 TxData register to output the character */
	RS232_TX_DATA = c;
}

unsigned char rs232_get_char() {
	/* Poll Rx bit in 6850 status register. Wait for it to become '1' */
	while ((RS232_STATUS & RS232_STATUS_MASK_RX_BIT) == 0)
		/* Wait */;

	/* Read received character from 6850 RxData register. */
	return RS232_RX_DATA;
}

int rs232_test_for_received_data(void) {
	/* Test Rx bit in 6850 serial comms chip status register */
	/* If RX bit is set, return TRUE, otherwise return FALSE */
	return ((RS232_STATUS & RS232_STATUS_MASK_RX_BIT) ? 1 : 0);
}
