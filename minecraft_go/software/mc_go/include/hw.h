/*
 * hw.h
 *
 *  Created on: Feb 2, 2016
 *      Author: derek
 */

#ifndef HW_H_
#define HW_H_

/**
 * Sets the green LEDs.
 *
 * The binary value of val is displayed on the LEDs
 */
void hw_led_green_set(const char val);

/**
 * Sets the green LEDs.
 *
 * The binary value of val is displayed on the LEDs
 */
void hw_led_red_set(const char val);

/**
 * Retrieves the value of the switches
 */
char hw_switches_get();

#endif /* HW_H_ */
