/*
 * rs232.h
 *
 *  Created on: Jan 14, 2016
 *      Author: derek
 */

#ifndef RS232_H_
#define RS232_H_

/**
 * Initializes the RS232 Port.
 *
 * Call this function at the start of the program prior to reading
 * or writing data via the RS232 port.
 */
void rs232_init(void);

/**
 * Writes a single character to the rs232 serial port
 */
void rs232_put_char(const unsigned char c);

/**
 * Reads a single character from the rs232 serial port
 */
unsigned char rs232_get_char();

/**
 * Poll the 6850 to determine if any character has been received.
 * It doesn't wait for one, or read it. It simply tests to see
 * if there is one available to read.
 */
int rs232_test_for_received_data(void);

#endif /* RS232_H_ */
