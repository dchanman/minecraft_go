/*
 * serial.h
 *
 *  Created on: Jan 14, 2016
 *      Author: derek
 */

#ifndef SERIAL_H_
#define SERIAL_H_

/**
 * Initializes the Serial Port.
 *
 * Call this function at the start of the program prior to reading
 * or writing data via the Serial port.
 */
void serial_init(unsigned volatile char * DEV_CONTROL, unsigned volatile char * DEV_BAUD);

/**
 * Writes a single character to the serial port
 */
void serial_put_char(const unsigned volatile char * DEV_STATUS, unsigned volatile char * DEV_TX_DATA, const unsigned volatile char c);

/**
 * Reads a single character from the rs232 serial port
 */
unsigned char serial_get_char(const unsigned volatile char * DEV_STATUS, const unsigned volatile char * DEV_RX_DATA);

/**
 * Poll the serial port to determine if any character has been received.
 * It doesn't wait for one, or read it. It simply tests to see
 * if there is one available to read.
 */
int serial_test_for_received_data(const unsigned volatile char * DEV_STATUS);

#endif /* SERIAL_H_ */