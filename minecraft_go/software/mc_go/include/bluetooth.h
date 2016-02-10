/*
 * bluetooth.h
 *
 *  Created on: 2016-01-25
 *      Author: Johnson
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define BLUETOOTH_NAME "Team21..."
#define BLUETOOTH_PIN "1337" //"1234"


// Bluetooth commands
#define BLUETOOTH_CMD_MODE "$$$"
#define BLUETOOTH_CMD_MODE_EXIT "---\r\n"
#define BLUETOOTH_SET_NAME_TEMPLATE "SN,%s\r\n" // ie. SN,DeviceName\r\n
#define BLUETOOTH_SET_PIN_TEMPLATE "SP,%s\r\n"  // ie. SP,1234\r\n
#define BLUETOOTH_FACTORY_RESET "SF,1\r\n"	// Restore to factory defaults


void bluetooth_init();
int bluetooth_send_cmd_from_template(const char *, const char *);
void bluetooth_send_command(const unsigned char *);
void bluetooth_echo_back_data();
unsigned char bluetooth_get_char();


#endif /* BLUETOOTH_H_ */
