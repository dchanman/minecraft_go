/*
 * GSP.h
 *
 *  Created on: 2016-01-17
 *      Author: Johnson
 */

#ifndef GSP_H_
#define GSP_H_

#define CR_CHAR '\r'
#define LF_CHAR '\n'

// GPS Commands
#define GSP_SNAPSHOT_NOW "$PMTK186,1*20\r\n"


char * GPS_retrive_data_line(int);
void GPS_send_command(const char *);
void GPS_init();

#endif /* GSP_H_ */
