/*
 * GSP.C
 *
 *  Created on: 2016-01-17
 *      Author: Johnson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "gps.h"
#include "serial.h"

#define GPS	((volatile unsigned char *)(0x84000210))

void gps_init() {
	serial_init(GPS, BAUD_RATE_9600);
}

void gps_put_char(const unsigned char c) {
	serial_put_char(GPS, c);
}

void gps_send_command(const char *command){
    int counter = 0;
    char curr_char = command[counter];
    
    while(curr_char != '\0'){
        gps_put_char(curr_char);
        curr_char = command[++counter];
    }
}

unsigned char gps_get_char() {
	return serial_get_char(GPS);
}

/*
 * Retrieves 1 line that is terminated by "\r\n" from GPS device
 */
bool gps_retrieve_data_line(char *buffer, int buffer_size){
	int char_count = 0;

	while (1){
		if (char_count >= buffer_size - 1){
			printf("Warning: Buffer not large enough for GPS data line; Cutting data line prematurely.");
			buffer[char_count] = '\0';
			return false;
		}

		char curr_char = gps_get_char();

		if (curr_char == CR_CHAR){
			if (gps_get_char() == LF_CHAR)
				break;
		} else {
			buffer[char_count] = curr_char;
			char_count++;
		}
	}

	buffer[char_count] = '\0';
	return true;
}


/*
 * Retrieves the data dump of GPS data logger. Return true if all data from dump
 * is placed in buffer.
 *
 * buffer - 2D array where each index will hold a data line
 */
bool gps_retrieve_data_dump(char **buffer, int buffer_size){
	//char **result = malloc(max_size * sizeof( char* ));
	int i;

	for (i = 0; i < buffer_size; i++) {
		char *data_line_buffer = malloc(GPS_DEFAULT_DATA_LINE_SIZE * sizeof(char));

		gps_retrieve_data_line(data_line_buffer, GPS_DEFAULT_DATA_LINE_SIZE);

		if (strstr(data_line_buffer, GPS_DATA_DUMP_END) != NULL)
			break;

		buffer[i] = data_line_buffer;

		if (i == buffer_size - 1){
			printf("Warning: Data dump reached max buffer size!\n");
			return false;
		}
	}

	return true;
}

bool gps_get_gga_data(char *data_line, GGA_data *buffer){
	const char delimiter[2] = ",";

	// to prevent the original data line from being modified
	char * data_line_copy[strlen(data_line)];
	strcpy(data_line_copy, data_line);

	char *token = strtok(data_line_copy, delimiter);

	if ( strcmp(token, GGA_IDENTIFIER) != 0) {
		//printf("Line is not in GGA format!\n");
		return false;
	}

	int count = 0;
	while( token != NULL ) {
		switch(count){
			case 1:
				strcpy(buffer->UTC_time, token);
				buffer->UTC_time[10] = '\0';
				break;
			case 2:
				strcpy(buffer->latitude, token);
				buffer->latitude[9] = '\0';
				break;
			case 3:
				strcpy(buffer->N_S, token);
				buffer->N_S[1] = '\0';
				break;
			case 4:
				strcpy(buffer->longitude, token);
				buffer->longitude[10] = '\0';
				break;
			case 5:
				strcpy(buffer->E_W, token);
				buffer->E_W[1] = '\0';
				break;
			case 7:
				strcpy(buffer->satellites, token);
				buffer->satellites[2] = '\0';
				break;
			default:
				break; // leave the other fields for now
		}

		//printf("Current token: %s \n", token);
		token = strtok(NULL, delimiter);

		count++;
	}

	return true;
}

int gps_get_rmc_data(char *data_line, RMC_data *buffer){
	const char delimiter[2] = ",";

	// to prevent the original data line from being modified
	char * data_line_copy[strlen(data_line)];
	strcpy(data_line_copy, data_line);

	char * token = strtok(data_line_copy, delimiter);

	if ( strcmp(token, RMC_IDENTIFIER) != 0) {
		//printf("Line is not in GGA format!\n");
		return false;
	}

	int count = 0;
	while( token != NULL ) {
		switch(count){
			case 1:
				strcpy(buffer->UTC_time, token);
				buffer->UTC_time[10] = '\0';
				break;
			case 3:
				strcpy(buffer->latitude, token);
				buffer->latitude[9] = '\0';
				break;
			case 4:
				strcpy(buffer->N_S, token);
				buffer->N_S[1] = '\0';
				break;
			case 5:
				strcpy(buffer->longitude, token);
				buffer->longitude[10] = '\0';
				break;
			case 6:
				strcpy(buffer->E_W, token);
				buffer->E_W[1] = '\0';
				break;
			case 7:
				strcpy(buffer->speed, token);
				buffer->speed[4] = '\0';
				break;
			case 9:
				strcpy(buffer->date, token);
				buffer->date[6] = '\0';
				break;
			default:
				break; // leave the out other fields
		}

		//printf("Current token: %s \n", token);
		token = strtok(NULL, delimiter);

		count++;
	}

	return true;
}


/*
 *  Get the most up to date RMC data. Return true if succeed before max_tries.
 *
 *  max_tries param is intend to prevent program from staling when GPS is not
 *  working and a value of 20 should be enough unless we are in the middle of
 *  a large data dump.
 */
bool getCurrentRMCdata(RMC_data *buffer, int max_tries){
	char *data_line_buffer = malloc(GPS_DEFAULT_DATA_LINE_SIZE * sizeof(char));

	int num_tries = 0;
	do {
		num_tries++;
		gps_retrieve_data_line(data_line_buffer, GPS_DEFAULT_DATA_LINE_SIZE);
	} while(!gps_get_rmc_data(data_line_buffer, buffer) && num_tries < max_tries);

	free(data_line_buffer);

	return num_tries >= max_tries ? false : true;
}


void convertRMCtoDateTime(RMC_data *RMC_data, DateTime *buffer){
	char RMC_year[3] = {0};
	strncpy(RMC_year, RMC_data->date+4, 2);
	buffer->year = atoi(RMC_year);

	char RMC_month[3] = {0};
	strncpy(RMC_month, RMC_data->date+2, 2);
	buffer->month = atoi(RMC_month);

	char RMC_day[3] = {0};
	strncpy(RMC_day, RMC_data->date, 2);
	buffer->day = atoi(RMC_day);

	char RMC_hour[3] = {0};
	strncpy(RMC_hour, RMC_data->UTC_time, 2);
	buffer->hour = atoi(RMC_hour);

	char RMC_minute[3] = {0};
	strncpy(RMC_minute, RMC_data->UTC_time+2, 2);
	buffer->minute = atoi(RMC_minute);

	char RMC_second[3] = {0};
	strncpy(RMC_second, RMC_data->UTC_time+4, 2);
	buffer->second = atoi(RMC_second);
}


/*
 *  Return elapsed time in seconds from start till finish
 *
 *  For simplicity, assume each year is 365 days, month is 30 days for now.
 */
unsigned long getElapsedInSeconds(DateTime *start, DateTime *finish){
	unsigned long start_in_seconds;
	unsigned long finish_in_seconds;

	start_in_seconds = start->year * 31536000 +
					   start->month * 2592000 +
					   start->day * 86400 +
					   start->hour * 3600 +
					   start->second;

	finish_in_seconds = finish->year * 31536000 +
					    finish->month * 2592000 +
					    finish->day * 86400 +
					    finish->hour * 3600 +
					    finish->second;

	return finish - start;
}

void convertSecondsToTime(Time *buffer, unsigned long seconds) {
	unsigned long left_over;

	buffer->hour = seconds / 3600;
	left_over = seconds % 3600;
	buffer->minute = (int) left_over / 60;
	buffer->second = (int) left_over % 60;
}


//---------------------------Timer Functions------------------------------//
void startTimer(DateTime *start_time){
	RMC_data *RMC_buffer = malloc(sizeof(RMC_data));

	if (!getCurrentRMCdata(RMC_buffer, GPS_DEFAULT_DATA_RETRIEVAL_TRIES))
		printf("Error: Unable to retrieve RMC data in %d tries.\n", GPS_DEFAULT_DATA_RETRIEVAL_TRIES);
	else
		convertRMCtoTime(RMC_buffer, start_time);

	free(RMC_buffer);
}

unsigned long stopTimer(DateTime *start_time){
	RMC_data *RMC_buffer = malloc(sizeof(RMC_data));
	DateTime *finish_time = malloc(sizeof(DateTime));

	if (!getCurrentRMCdata(RMC_buffer, GPS_DEFAULT_DATA_RETRIEVAL_TRIES))
		printf("Error: Unable to retrieve RMC data in %d tries.\n", GPS_DEFAULT_DATA_RETRIEVAL_TRIES);
	else
		convertRMCtoTime(RMC_buffer, finish_time);

	free(RMC_buffer);
	free(finish_time);

	return getElapsedInSeconds(start_time, finish_time);
}
//--------------------------End Timer Functions---------------------------//



/*
 * Return the speed in km/h (converted from knots)
 *
 * Note: GPS can claim speed of up to 0.09km/h even
 * when not moving due to device limitations
 */
float getSpeedFromRMC(RMC_data *RMC_data){
	float speed_knots = atof(RMC_data->speed);

	return speed_knots * 1.852; // 1 knots = 1.852 km/h
}




void gps_checksum(char *string, int size) {
  int i;
  char result = string[0];
  for(i = 1; i < size; i++){
	printf("XORing: %c %d ", string[i], string[i]);
    result ^= string[i];
  }

  printf("Checksum: %x \n", result);
}





//------------------------- FOR PARSING DATA DUMP-----------------------------//
    
// see http://stackoverflow.com/questions/2182002/convert-big-endian-to-
// little-endian-in-c-without-using-provided-func
// takes a 4 byte float in string form (8 chars) and converts to 4 byte form
// (still stored in an int but in float form)
// and swaps the bytes order the reason for this is the GPS outputs the
// longitude and latitude LOG data in 4 byte float form but as little endian
// NIOS however uses big endian
int swapEndian(char *s)
{
    register int val;
    val = strtoul(s, NULL, 16) ; // convert to 4 byte int form in base 16
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
    val = (val << 16) | ((val >> 16) & 0xFFFF);
    return val;
}

// these two functions take a 4 byte IEEE-754 format float
// (passed as a 4 byte int representing latitude and longitude values)
// in big endian format and converts it to an ASCII decimal string
// which it returns with decimal point in the string.
char *FloatToLatitudeConversion(int x) //output format is xx.yyyy
{
    static char buff[100];
    float *ptr = (float *)(&x) ; // cast int to float
    float f = *ptr ; // get the float
    sprintf(buff, "%2.4f", f); // write in string to an array
    return buff;
}

char *FloatToLongitudeConversion(int x) // output format is (-)xxx.yyyy
{
    static char buff[100];
    float *ptr = (float *)(&x);
    float f = *ptr;
    sprintf(buff, "%3.4f", f);
    return buff;
}

