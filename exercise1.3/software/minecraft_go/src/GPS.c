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
#include "GPS.h"
#include "serial.h"

#define GPS_CONTROL	((volatile unsigned char *)(0x84000210))
#define GPS_STATUS	((volatile unsigned char *)(0x84000210))
#define GPS_TX_DATA	((volatile unsigned char *)(0x84000212))
#define GPS_RX_DATA	((volatile unsigned char *)(0x84000212))
#define GPS_BAUD	((volatile unsigned char *)(0x84000214))

void GPS_init() {
	//serial_init(GPS_CONTROL, GPS_BAUD);

	*GPS_CONTROL = 0x95;
	*GPS_BAUD = 0x7; // 0b111 to select 9600 baud

}

void GPS_put_char(const unsigned char c) {
	serial_put_char(GPS_STATUS, GPS_TX_DATA, c);
}

void GPS_send_command(const char *command){
    int counter = 0;
    char curr_char = command[counter];
    
    while(curr_char != '\0'){
        GPS_put_char(curr_char);
        curr_char = command[++counter];
    }
}

unsigned char GPS_get_char() {
	return serial_get_char(GPS_STATUS, GPS_RX_DATA);
}

char * GPS_retrive_data_line(int buffer_size){
	// maybe make the caller supply buffer for easier prevention of memory leaking?
	char * buffer = malloc(buffer_size * sizeof(char));
	int char_count = 0;

	while (1){
		if (char_count >= buffer_size - 2){
			printf("Warning: Buffer not large enough for GPS data line; Cutting data line prematurely.");
			break;
		}

		char curr_char = GPS_get_char();

		if (curr_char == CR_CHAR){
			if (GPS_get_char() == LF_CHAR)
				break;
		} else {
			buffer[char_count] = curr_char;
			char_count++;
		}
	}

	buffer[char_count] = '\0';

	return buffer;
}


char ** GPS_retrive_data_dump(max_size){
	char **result = malloc(max_size * sizeof( char* ));
	int i;

	for (i = 0; i < max_size; i++) {
		char * current_string = GPS_retrive_data_line(1000);

		if (strstr(current_string, GPS_DATA_DUMP_END) != NULL)
			break;

		result[i] = current_string;

		if (i == max_size - 1)
			printf("Warning: Data dump reached max buffer size!\n");
	}

	return result;
}

    
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
