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

char * gps_retrive_data_line(int buffer_size){
	// maybe make the caller supply buffer for easier prevention of memory leaking?
	char * buffer = malloc(buffer_size * sizeof(char));
	int char_count = 0;

	while (1){
		if (char_count >= buffer_size - 2){
			printf("Warning: Buffer not large enough for GPS data line; Cutting data line prematurely.");
			break;
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

	return buffer;
}


char ** gps_retrive_data_dump(max_size){
	char **result = malloc(max_size * sizeof( char* ));
	int i;

	for (i = 0; i < max_size; i++) {
		char * current_string = gps_retrive_data_line(1000);

		if (strstr(current_string, GPS_DATA_DUMP_END) != NULL)
			break;

		result[i] = current_string;

		if (i == max_size - 1)
			printf("Warning: Data dump reached max buffer size!\n");
	}

	return result;
}

int gps_get_gga_data(char *GGA_line, struct gga_data *holder){
	const char delimiter[2] = ",";
	char * token = strtok(GGA_line, delimiter);

	if ( strcmp(token, GGA_IDENTIFIER) != 0) {
		//printf("Line is not in GGA format!\n");
		return 0;
	}

	int count = 0;
	while( token != NULL ) {
		switch(count){
			case 1:
				memcpy(holder->UTC_time, token, strlen(token));
				holder->UTC_time[10] = '\0';
				break;
			case 2:
				memcpy(holder->latitude, token, strlen(token));
				holder->latitude[9] = '\0';
				break;
			case 3:
				memcpy(holder->N_S, token, strlen(token));
				holder->N_S[1] = '\0';
				break;
			case 4:
				memcpy(holder->longitude, token, strlen(token));
				holder->longitude[10] = '\0';
				break;
			case 5:
				memcpy(holder->E_W, token, strlen(token));
				holder->E_W[1] = '\0';
				break;
			case 7:
				memcpy(holder->satellites, token, strlen(token));
				holder->satellites[2] = '\0';
				break;
			default:
				break; // leave the other fields for now
		}

		//printf("Current token: %s \n", token);
		token = strtok(NULL, delimiter);

		count++;
	}

	return 1;
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

//------------------------- FOR PARSING DATA DUMP
    
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

void checksum(char string[], int size) {
  int i;
  char result = string[0];
  for(i = 1; i < size; i++){
	printf("XORing: %c %d ", string[i], string[i]);
    result ^= string[i];
  }

  printf("Checksum: %x \n", result);
}
