/*
 * GSP.h
 *
 *  Created on: 2016-01-17
 *      Author: Johnson
 */

#ifndef GSP_H_
#define GSP_H_


// GPS Commands
#define GPS_SNAPSHOT_NOW "$PMTK186,1*20\r\n"

#define GPS_STOP_DATA_LOG "$PMTK185,1*23\r\n"
#define GPS_START_DATA_LOG "$PMTK185,0*22\r\n"

#define GPS_DATA_DUMP_PARTIAL "$PMTK622,1*29\r\n"
#define GPS_DATA_DUMP_END "$PMTKLOX,2*47\r\n"

#define GGA_IDENTIFIER "$GPGGA"

struct gga_data {
	char UTC_time[11];
	char latitude[10];
	char N_S[2];
	char longitude[11];
	char E_W[2];
	char satellites[3];
};

char * gps_retrive_data_line(int);
void gps_send_command(const char *);
void gps_init();
int gps_get_gga_data(char *, struct gga_data *);
void gps_checksum(char *, int);

#endif /* GSP_H_ */
