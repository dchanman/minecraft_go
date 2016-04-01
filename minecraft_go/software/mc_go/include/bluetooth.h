/*
 * bluetooth.h
 *
 *  Created on: 2016-01-25
 *      Author: Johnson
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define BLUETOOTH_NAME "Team21"
#define BLUETOOTH_PIN "4321" //"1234"


// Bluetooth commands
#define BLUETOOTH_CMD_MODE "$$$"
#define BLUETOOTH_CMD_MODE_EXIT "---\r\n"
#define BLUETOOTH_SET_NAME_TEMPLATE "SN,%s\r\n" // ie. SN,DeviceName\r\n
#define BLUETOOTH_SET_PIN_TEMPLATE "SP,%s\r\n"  // ie. SP,1234\r\n
#define BLUETOOTH_FACTORY_RESET "SF,1\r\n"	// Restore to factory defaults


void bluetooth_init();
void bluetooth_put_char(const unsigned char c);
unsigned char bluetooth_get_char();
void bluetooth_get_n_char(unsigned char *recv_msg, const int recv_msg_length);
void bluetooth_send_command(const unsigned char *command);
void bluetooth_send_data(const unsigned char *command, const int length);
int bluetooth_send_cmd_from_template(const char *cmd_template, const char *value);
void bluetooth_echo_back_data();


#endif /* BLUETOOTH_H_ */
