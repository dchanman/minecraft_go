#include <stdint.h>
#include <stdio.h>

#include "minigames.h"
#include "project1_demo.h"

/* Comment this #define out when we're done testing */
#define TESTING

#ifdef TESTING
#include "test.h"
#endif

#include <sys/alt_irq.h>
#include <sys/alt_alarm.h>
#include <altera_avalon_timer.h>
#include "altera_avalon_pio_regs.h"
#include <altera_avalon_timer_regs.h>
#define TIMER0	((volatile short int *) 0x100010e0)
#define TIMER1	((volatile short int *) 0x100010c0)

static volatile int counter = 0;

static void timer_isr(void * context)
{
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0, 0);
	counter++;
	printf("ISR: %d\n", counter);
}

static void test_interrupts()
{
	/* Configure timer */

	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, 0x0001);
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);


	/**
	 * period_n registers:
	 * Sets the timer length
	 * 50000000 cycles at 50MHz = 1 second
	 * 50000000 = 0x02FAF080
	 */
	//*(TIMER0 + 2) = 0xF080;
	//*(TIMER0 + 3) = 0x02FA;

	//IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER0, 0x9f00);
	//IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER0, 0x0024);
	IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, 0xF080);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, 0x02FA);

	/* Configure interrupts */
	alt_irq_enable(TIMER_0_IRQ);
	alt_irq_register(TIMER_0_IRQ, NULL, timer_isr);
	//alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, timer_isr, NULL, 0);

	printf("Starting timer...\n");
	short int setting = IORD_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE);
	setting &= 0x0007; // set STOP to 0
	setting |= 0x0004; // set START to 1
	printf("Setting: 0x%x\n", setting);
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, setting);


	/* Start the timer */
	//*(TIMER0 + 1) &= 0x0007; // set STOP to 0
	//*(TIMER0 + 1) |= 0x0004; // set START to 1
}

int main() {
	printf("Minecraft GO\n");

	/* Uncomment the feature you want to test */
	//rs232_test_multi_char();
	//rs232_test_single_char();
	//sdcard_test_open();
	//sdcard_test();
	//gps_test();

	//savefile_test();
	//gps_test();
	//minecraft_rpc_test_main();
	//minecraft_rpc_test_protocol_msg();
	//bluetooth_test();
	//touchscreen_test();
	//sprint1_demo();
	//graphics_test();
	//int health = PLAYER_MAX_HEALTH;
	//minigame_creeper_encounter(&health);
	//minigame_digging();

	//project1_demo_initialize_savefile();
	//project1_demo_main();
	//journey_display_test();

	//test_interrupts();
	//test_int2();

	//printf("Start\n");

	//timer_test();

	//while((*(short int *)TIMER_0_BASE & 0x2) == 0x2)
	//	;


	//printf("Done\n");

	return 0;
}


