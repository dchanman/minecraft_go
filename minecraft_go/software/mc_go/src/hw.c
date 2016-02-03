/*
 * hw.c
 *
 *  Created on: Feb 2, 2016
 *      Author: derek
 */

#define SWITCHES (volatile char *) (0x80001050)
#define GREEN_LEDS (char *) (0x80001030)
#define RED_LEDS (char *) (0x80001040)

void hw_led_green_set(const char val) {
	*GREEN_LEDS = val;
}

void hw_led_red_set(const char val) {
	*RED_LEDS = val;
}

char hw_switches_get() {
	return *SWITCHES;
}
