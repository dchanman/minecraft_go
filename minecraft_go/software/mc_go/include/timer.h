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
	TIMER_ONESHOT = 0,
	TIMER_CONTINUOUS
} timer_type_t;

void timer_init(const int timer_id, timer_type_t timer_type, alt_isr_func handler);
void timer_set(const int timer_id, int seconds);
void timer_start(const int timer_id);
void timer_stop(const int timer_id);
boolean timer_is_running(const int timer_id);

#endif /* TIMER_H_ */
