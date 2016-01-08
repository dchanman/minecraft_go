/*
 * Exercise 1.1
 *
 * Team 21
 * Derek Chan, Jay Dahiya, Johnson Huang, Logan Gilmore
 *
 */

#include <stdio.h>
#include "altera_up_avalon_character_lcd.h"

#define switches (volatile char *) 0x0002000
#define pushbuttons (volatile char *) 0x0002040
#define leds (char *) 0x0002010
#define LCD_DEV "/dev/character_lcd_0"

static const char KEY_MASKS[] = { 0x1, 0x2, 0x4, 0x8 };

static void lcd_replace_last_char(alt_up_character_lcd_dev * char_lcd_dev, const char c);

int main() {
	/* For pushbuttons, 1 means unpressed */
	char last_key_value[4] = { 1 };
	char key_value;
	alt_up_character_lcd_dev * char_lcd_dev;

	/* Console preamble */
	printf("Exercise 1.1\n"
			"Team 21\n"
			"Derek Chan, Jay Dahiya, Johnson Huang, Logan Gilmore\n");

	/* Initialize and open the LCD Driver */
	char_lcd_dev = alt_up_character_lcd_open_dev(LCD_DEV);
	if (char_lcd_dev == NULL)
		printf("Error: Could not open character LCD device %s\n", LCD_DEV);

	alt_up_character_lcd_init(char_lcd_dev);
	alt_up_character_lcd_string(char_lcd_dev, "Key:  ");

	/* Main loop */
	while (1) {
		/* Toggle LEDG with the SW */
		*leds = *switches;

		/* Read KEY0 */
		key_value = *pushbuttons & KEY_MASKS[0];
		if (key_value != last_key_value[0]) {
			last_key_value[0] = key_value;
			if (key_value == 0) {
				printf("KEY0\n");
				lcd_replace_last_char(char_lcd_dev, '0');
			}
		}

		/* Read KEY1 */
		key_value = *pushbuttons & KEY_MASKS[1];
		if (key_value != last_key_value[1]) {
			last_key_value[1] = key_value;
			if (key_value == 0) {
				printf("KEY1\n");
				lcd_replace_last_char(char_lcd_dev, '1');
			}
		}

		/* Read KEY2 */
		key_value = *pushbuttons & KEY_MASKS[2];
		if (key_value != last_key_value[2]) {
			last_key_value[2] = key_value;
			if (key_value == 0) {
				printf("KEY2\n");
				lcd_replace_last_char(char_lcd_dev, '2');
			}
		}

		/* Read KEY3 */
		key_value = *pushbuttons & KEY_MASKS[3];
		if (key_value != last_key_value[3]) {
			last_key_value[3] = key_value;
			if (key_value == 0) {
				printf("KEY3\n");
				lcd_replace_last_char(char_lcd_dev, '3');
			}
		}
	}

	return 0;
}

/**
 * Replaces the last character in the LCD
 */
static void lcd_replace_last_char(alt_up_character_lcd_dev * char_lcd_dev, const char c) {
	/* Normally we would use sprintf, but this takes fewer operations */
	char lcd_string[2];
	lcd_string[0] = c;
	lcd_string[1] = '\0';

	/* Overwrite the last char on the LCD */
	alt_up_character_lcd_shift_cursor(char_lcd_dev, -1);
	alt_up_character_lcd_string(char_lcd_dev, lcd_string);
}
