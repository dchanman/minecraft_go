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
 * Writes a buffer to the rs232 serial port
 */
void rs232_put_n_char(const unsigned char * msg, const int msg_length);

/**
 * Reads a single character from the rs232 serial port
 */
unsigned char rs232_get_char();

/**
 * Fills a buffer with reads from the rs232 serial port.
 *
 * Note that calling this function is BLOCKING. This means that this function will
 * not return until the entire buffer is filled.
 */
void rs232_get_n_char(unsigned char * recv_msg, const int recv_msg_length);

/**
 * Poll the 6850 to determine if any character has been received.
 * It doesn't wait for one, or read it. It simply tests to see
 * if there is one available to read.
 */
int rs232_test_for_received_data(void);

#endif /* RS232_H_ */
