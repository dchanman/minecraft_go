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

static void rs232_init(void);
static int rs232_put_char(int c);
static int rs232_get_char(void);
static int rs232_test_for_received_data(void);

int main()
{
  printf("Hello from Nios II!\n");

  return 0;
}

/**
 * Initializes the RS232 Port.
 *
 * Call this function at the start of the program prior to reading
 * or writing data via the RS232 port.
 */
static void rs232_init(void)
{
	// set up 6850 Control Register to utilise a divide by 16 clock,
	// set RTS low, use 8 bits of data, no parity, 1 stop bit,
	// transmitter interrupt disabled
	// program baud rate generator to use 115k baud
}

static int rs232_put_char(int c)
{
	// poll Tx bit in 6850 status register. Wait for it to become '1'
	// write 'c' to the 6850 TxData register to output the character
	return c;
}

static int rs232_get_char(void)
{
	// poll Rx bit in 6850 status register. Wait for it to become '1'
	// read received character from 6850 RxData register.
}

/**
 * Poll the 6850 to determine if any character has been received.
 * It doesn't wait for one, or read it. It simply tests to see
 * if there is one available to read.
 */
static int rs232_test_for_received_data(void)
{
	// Test Rx bit in 6850 serial comms chip status register
	// if RX bit is set, return TRUE, otherwise return FALSE
}
