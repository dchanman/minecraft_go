/*
 * timer.h
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "general.h"
#include <sys/alt_irq.h>

#define NUM_TIMERS	2

typedef enum {
	/* Timer runs to 0 and then stops */
	TIMER_ONESHOT = 0,
	/* Timer runs to 0 and then restarts */
	TIMER_CONTINUOUS
} timer_type_t;

/**
 * Initializes the timer
 *
 * YOUR ISR MUST CALL TIMER_CLEAR!!!!!!!!
 *
 * Note that the interrupt service routine (ISR) CANNOT call printf.
 * Well it can, but you risk deadlocking yourself if you get interrupted
 * while the main thread is doing a printf
 *
 * @param timer_id - 0 or 1
 * @param timer_type - TIMER_ONESHOT or TIMER_CONTINUOUS
 * @param isr - name of a function to call as an interrupt service routine
 */
void timer_init(const int timer_id, const timer_type_t timer_type, alt_isr_func isr);

/**
 * Clears the timer.
 *
 * This MUST be called from an interrupt service routine (ISR), otherwise
 * the interrupt will loop indefinitely
 */
void timer_clear(const int timer_id);

/**
 * Sets the millisecond count of the timer
 *
 * @param timer_id - 0 or 1
 * @param millis - millisecond count
 */
void timer_set(const int timer_id, const int millis);

/**
 * Starts the timer
 *
 * @param timer_id
 */
void timer_start(const int timer_id);

/**
 * Stops the timer
 *
 * @param timer_id
 */
void timer_stop(const int timer_id);

/**
 * Determines if the timer is running
 *
 * @param timer_id
 * @returns TRUE if timer is running, FALSE otherwise
 */
boolean timer_is_running(const int timer_id);

#endif /* TIMER_H_ */
