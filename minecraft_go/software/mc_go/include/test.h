/*
 * test.h
 *
 *  Created on: Jan 18, 2016
 *      Author: derek
 */

#ifndef TEST_H_
#define TEST_H_

int rs232_test_single_char();
int rs232_test_multi_char();
int sdcard_test_open(void);
void sdcard_test();
void gps_test();
void touchscreen_test();
void touchscreen_test_timeout();
void minecraft_rpc_test_rs232_send_and_recv_echo();
void minecraft_rpc_test_protocol_msg();
void bluetooth_test();
void sprint1_demo();
void savefile_test();
void timer_test();
void picture_transfer_test();


#endif /* TEST_H_ */
