/*
 * timer_test.c
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */
#include <stdio.h>
#include "timer.h"

#include <unistd.h>

static int counter0 = 0;
static int counter1 = 0;

static void timer_0_isr(void * context) {
	timer_clear(0);
	counter0++;
}

static void timer_1_isr(void * context) {
	timer_clear(1);
	counter1++;
}

void timer_test() {
	/* Initialize timers */
	printf("Init\n");
	timer_init(0, TIMER_CONTINUOUS, timer_0_isr);
	timer_init(1, TIMER_ONESHOT, timer_1_isr);

	printf("Set\n");
	timer_set(0, 1000);
	timer_set(1, 2000);

	printf("Start\n");
	usleep(1000000);
	timer_start(0);
	timer_start(1);

	counter0 = 0;
	counter1 = 0;
	while (counter0 < 5) {
		printf("Timer 0: %d Timer 1: %d\n", counter0, counter1);
		usleep(1000000);
	}

	printf("Timer 0: %s\n", (timer_is_running(0) ? "running" : "stopped"));
	printf("Timer 1: %s\n", (timer_is_running(1) ? "running" : "stopped"));

	timer_start(1);
	while (counter0 < 10) {
		printf("Timer 0: %d Timer 1: %d\n", counter0, counter1);
		usleep(1000000);
	}

	printf("Timer 0: %s\n", (timer_is_running(0) ? "running" : "stopped"));
	printf("Timer 1: %s\n", (timer_is_running(1) ? "running" : "stopped"));

	timer_stop(0);
	timer_stop(1);

	printf("Timer 0: %s\n", (timer_is_running(0) ? "running" : "stopped"));
	printf("Timer 1: %s\n", (timer_is_running(1) ? "running" : "stopped"));

	printf("Done!\n");
}

