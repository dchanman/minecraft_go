/*
 * timer.c
 *
 *  Created on: Feb 24, 2016
 *      Author: derek
 */

#include "general.h"
#include "timer.h"
#include <sys/alt_irq.h>
#include <altera_avalon_timer.h>
#include <altera_avalon_timer_regs.h>

/* Mappings to altera macros */
static short int * timer_base_map[] = { TIMER_0_BASE, TIMER_1_BASE };

static short int timer_irq_map[] = { TIMER_0_IRQ, TIMER_1_IRQ };

static int timer_freq_map[] = { TIMER_0_FREQ, TIMER_1_FREQ };

/* Mappings to timer types */
/**
 * Status Register:
 * Bit 0: ITO - interrupt on
 * Bit 1: CONT - timer restarts after hitting 0
 * Bit 2: START - starts timer
 * Bit 3: STOP - stops timer
 */
static short int timer_type_map[] = {
/* TIMER_ONESHOT */
0x0001,
/* TIMER_CONTINUOUS */
0x0003 };

void timer_init(const int timer_id, timer_type_t timer_type, alt_isr_func handler) {
	if (timer_id < 0 || timer_id > NUM_TIMERS) {
		printf("[%s]: Error: timer_id out of range.\n", __func__);
		return;
	}

	/* Enable interrupts */
	alt_irq_enable(timer_irq_map[timer_id]);
	alt_irq_register(timer_irq_map[timer_id], NULL, handler);

	/* Configure timer */
	IOWR_ALTERA_AVALON_TIMER_CONTROL(timer_base_map[timer_id], timer_type_map[timer_type]);
	IOWR_ALTERA_AVALON_TIMER_STATUS(timer_base_map[timer_id], 0);
}

void timer_set(const int timer_id, int seconds) {
	/* The timers have two 16-bit registers */
	short int seconds_high;
	short int seconds_low;
	long cycles;

	cycles = seconds * timer_freq_map[timer_id];

	seconds_high = 0xFFFF & (seconds >> 8);
	seconds_low = seconds & 0xFFFF;

	IOWR_ALTERA_AVALON_TIMER_PERIODL(timer_base_map[timer_id], seconds_low);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(timer_base_map[timer_id], seconds_high);
}

void timer_start(const int timer_id) {
	short int setting;

	if (timer_id < 0 || timer_id > NUM_TIMERS) {
		printf("[%s]: Error: timer_id out of range.\n", __func__);
		return;
	}

	setting = IORD_ALTERA_AVALON_TIMER_CONTROL(timer_base_map[timer_id]);
	setting &= 0x0007; // set STOP to 0
	setting |= 0x0004; // set START to 1
	IOWR_ALTERA_AVALON_TIMER_CONTROL(timer_base_map[timer_id], setting);
}

void timer_stop(const int timer_id) {
	short int setting;

	if (timer_id < 0 || timer_id > NUM_TIMERS) {
		printf("[%s]: Error: timer_id out of range.\n", __func__);
		return;
	}

	setting = IORD_ALTERA_AVALON_TIMER_CONTROL(timer_base_map[timer_id]);
	setting |= 0x0008; // set STOP to 1
	setting &= 0x000B; // set START to 0
	IOWR_ALTERA_AVALON_TIMER_CONTROL(timer_base_map[timer_id], setting);
}

boolean timer_is_running(const int timer_id) {
	short int data;

	data = IORD_ALTERA_AVALON_TIMER_STATUS(timer_base_map[timer_id]);
	if ((data & 0x02) == 0x02)
		return TRUE;
	else
		return FALSE;
}
