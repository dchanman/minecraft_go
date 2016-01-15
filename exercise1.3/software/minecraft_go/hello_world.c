/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdint.h>
#include <stdio.h>

#define RS232_CONTROL	(*(volatile uint8_t *)(0x84000200))
#define RS232_STATUS	(*(volatile uint8_t *)(0x84000200))
#define RS232_TX_DATA	(*(volatile uint8_t *)(0x84000202))
#define RS232_RX_DATA	(*(volatile uint8_t *)(0x84000202))
#define RS232_BAUD		(*(volatile uint8_t *)(0x84000204))

#define RS232_STATUS_MASK_TX_BIT	(0x02)
#define RS232_STATUS_MASK_RX_BIT	(0x01)

#define CPEN_EXIT_OK 0

static void rs232_init(void);
static int rs232_put_char(const uint8_t c);
static int rs232_get_char(uint8_t *data);
static int rs232_test_for_received_data(void);

int main() {
	printf("Minecraft GO Base Platform\n");

	rs232_init();

	/* Test program to check communication to Hyperterminal/GtkTerm */
	uint8_t recv;
	while (1) {
		rs232_get_char(&recv);
		printf("Received <%c> <0x%x>\n", recv, recv);

		rs232_put_char(recv);
	}

	return 0;
}

/**
 * Initializes the RS232 Port.
 *
 * Call this function at the start of the program prior to reading
 * or writing data via the RS232 port.
 */
static void rs232_init(void) {
	// set up 6850 Control Register to utilise a divide by 16 clock,
	// set RTS low, use 8 bits of data, no parity, 1 stop bit,
	// transmitter interrupt disabled
	/**
	 * Set up 6850 Control Register to use
	 * * Divide by 16 clock (CR1/CR0 = 01)
	 * * 8-bit data, no parity, 1 stop bit (CR4/CR3/CR2 = 101)
	 * * RTS low, Transmitting Interrupt Disabled (CR6/CR5 = 00)
	 * * Receive Interrupt Enable - Set to 0 arbitrarily (CR7 = 0)
	 *
	 * 0b00010101 = 0x15
	 */
	RS232_CONTROL = 0x15;

	// program baud rate generator to use 115k baud
	RS232_BAUD = 0x01;
}

static int rs232_put_char(const uint8_t c) {
	/* Poll Tx bit in 6850 status register. Wait for it to become '1' */
	while ((RS232_STATUS & RS232_STATUS_MASK_TX_BIT) == 0)
		/* Wait */;

	//* Write 'c' to the 6850 TxData register to output the character */
	RS232_TX_DATA = c;

	return CPEN_EXIT_OK;
}

static int rs232_get_char(uint8_t *data) {
	/* Poll Rx bit in 6850 status register. Wait for it to become '1' */
	while ((RS232_STATUS & RS232_STATUS_MASK_RX_BIT) == 0)
		/* Wait */;

	/* Read received character from 6850 RxData register. */
	*data = RS232_RX_DATA;

	return CPEN_EXIT_OK;
}

/**
 * Poll the 6850 to determine if any character has been received.
 * It doesn't wait for one, or read it. It simply tests to see
 * if there is one available to read.
 */
static int rs232_test_for_received_data(void) {
	/* Test Rx bit in 6850 serial comms chip status register */
	/* If RX bit is set, return TRUE, otherwise return FALSE */
	return ((RS232_STATUS & RS232_STATUS_MASK_RX_BIT) ? 1 : 0);
}
