/*
 * picture_transfer.h
 *
 *  Created on: Mar 29, 2016
 *      Author: Logan
 */

#ifndef PICTURE_TRANSFER_H_
#define PICTURE_TRANSFER_H_

//
#define PICTURE_STRING_LENGTH 1
#define PICTURE_CONNECTION_CHECK_LENGTH 1

#define WAIT 1
#define STRING_LENGTH 2
#define MESSAGE_LENGTH 3
#define FINAL 4

/**
 * Initialize the bluetooth
 */
void picture_transfer_init();

/**
 * Receives a message from the serial port over bluetooth
 *
 * @param recv_msg - pointer to a message that will be received
 */
void picture_transfer_receive(unsigned char *recv_msg);

/**
 * Sends a message using the serial port over bluetooth
 *
 * @param sent_msg - pointer to a message that will be sent
 * @param send_msg_length - pointer to length of message
 * @param length_of_send_msg_length - pointer to number of characters in send_msg_length
 */
void picture_transfer_send(unsigned char *filename);

#endif /* PICTURE_TRANSFER_H_ */
