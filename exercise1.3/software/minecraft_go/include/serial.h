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
void serial_init(unsigned volatile char * DEV);

/**
 * Writes a single character to the serial port
 */
void serial_put_char(unsigned volatile char * DEV, const unsigned char c);

/**
 * Writes an array of characters to the serial port
 *
 * @param DEV - the address of the serial port device
 * @param msg - the address of an array containing characters
 * @param msg_length - the number of characters to write to the device
 */
void serial_put_n_char(unsigned volatile char * DEV, const unsigned char * msg, const int msg_length);

/**
 * Reads a single character from the rs232 serial port
 */
unsigned char serial_get_char(const unsigned volatile char * DEV);

/**
 * Reads a sequence of characters from the serial port.
 *
 * @param DEV - the address of the serial port device
 * @param recv_msg - a buffer to store all received characters
 * @param recv_msg_length - the number of characters to read into the buffer
 */
void serial_get_n_char(const unsigned volatile char * DEV, unsigned char * recv_msg, const int recv_msg_length);

/**
 * Poll the serial port to determine if any character has been received.
 * It doesn't wait for one, or read it. It simply tests to see
 * if there is one available to read.
 */
int serial_test_for_received_data(const unsigned volatile char * DEV);

#endif /* SERIAL_H_ */
