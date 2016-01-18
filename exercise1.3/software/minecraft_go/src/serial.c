/*
 * serial.c
 *
 *  Created on: Jan 14, 2016
 *      Author: derek
 */

#include "general.h"
#include "serial.h"

#define SERIAL_STATUS_MASK_TX_BIT	(0x02)
#define SERIAL_STATUS_MASK_RX_BIT	(0x01)

#define DEV_CONTROL	(DEV)
#define DEV_STATUS	(DEV)
#define DEV_TX_DATA	(DEV + 2)
#define DEV_RX_DATA	(DEV + 2)
#define DEV_BAUD	(DEV + 4)

void serial_init(unsigned volatile char * DEV) {
	/**
	 * Set up 6850 Control Register to use
	 * * Divide by 16 clock (CR1/CR0 = 01)
	 * * 8-bit data, no parity, 1 stop bit (CR4/CR3/CR2 = 101)
	 * * RTS low, Transmitting Interrupt Disabled (CR6/CR5 = 00)
	 * * Receive Interrupt Enable - Set to 1 arbitrarily (CR7 = 1)
	 *
	 * 0b10010101 = 0x95
	 */
	*DEV_CONTROL = 0x95;

	// program baud rate generator to use 115k baud
	*DEV_BAUD = 0x01;
}

void serial_put_char(const unsigned volatile char * DEV, const unsigned char c) {
	/* Poll Tx bit in 6850 status register. Wait for it to become '1' */
	while ((*DEV_STATUS & SERIAL_STATUS_MASK_TX_BIT) == 0)
		/* Wait */;

	//* Write 'c' to the 6850 TxData register to output the character */
	*DEV_TX_DATA = c;
}

unsigned char serial_get_char(const unsigned volatile char * DEV) {
	/* Poll Rx bit in 6850 status register. Wait for it to become '1' */
	while ((*DEV_STATUS & SERIAL_STATUS_MASK_RX_BIT) == 0)
		/* Wait */;

	/* Read received character from 6850 RxData register. */
	return (*DEV_RX_DATA);
}

int serial_test_for_received_data(const unsigned volatile char * DEV) {
	/* Test Rx bit in 6850 serial comms chip status register */
	/* If RX bit is set, return TRUE, otherwise return FALSE */
	return ((*DEV_STATUS & SERIAL_STATUS_MASK_RX_BIT) ? 1 : 0);
}

int serial_put_n_char(const unsigned volatile char * DEV, const )
