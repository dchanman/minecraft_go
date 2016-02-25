/*
 * timer_test.c
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */
#include <stdio.h>
#include "timer.h"

static alt_isr_func timer_0_isr() {
	static int counter = 0;
	counter++;
	printf("Timer 0: %d\n", counter);
	return 0;
}

static alt_isr_func timer_1_isr() {
	static int counter = 0;
	counter++;
	printf("Timer 1: %d\n", counter);
	return 0;
}

void timer_test() {
	/* Initialize timers */
	printf("Init\n");
	timer_init(0, TIMER_CONTINUOUS, timer_0_isr);
	timer_init(1, TIMER_ONESHOT, timer_1_isr);

	printf("Set\n");
	timer_set(0, 1);
	timer_set(1, 1);

	printf("Start\n");
	timer_start(0);
	timer_start(1);

	while (timer_is_running(0))
		;

	printf("Done!\n");
}

