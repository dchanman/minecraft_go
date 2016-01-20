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
#define GPS_SNAPSHOT_NOW "$PMTK186,1*20\r\n"

#define GPS_STOP_DATA_LOG "$PMTK185,1*23\r\n"
#define GPS_START_DATA_LOG "$PMTK185,0*22\r\n"

#define GPS_DATA_DUMP_PARTIAL "$PMTK622,1*29\r\n"
#define GPS_DATA_DUMP_END "$PMTKLOX,2*47\r\n"


char * GPS_retrive_data_line(int);
void GPS_send_command(const char *);
void GPS_init();
void checksum(char[], int);

#endif /* GSP_H_ */
