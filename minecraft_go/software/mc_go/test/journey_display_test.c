/*
 * journey_display.c
 *
 *  Created on: 2016-02-23
 *      Author: Johnson
 */

#include "hw.h"
#include "general.h"
#include "journey_display.h"
#include "graphics.h"

void journey_display_test(){

	Time time1 = {21, 45, 22};

	char sw;

	int first_try = 0;

	graphics_clear_screen();

	/* Demo loop */
	while (1) {
		/* Hardware controls */

		sw = hw_switches_get();
		switch (sw) {
		case 0x00:
			/* Do nothing */
			first_try = 0;
			break;

		case 0x01:

			if(first_try == 0){
				displayBackground();
				first_try = 1;
				displayMenu(140, 141);
			}


			break;

		case 0x02:

			if(first_try == 0){
						displayBackground();
						first_try = 1;
						displayMenu(90, 100);
									displayElapsedTime(&time1, 100, 200);
									displayDestDistance(54.35, 100, 250);
									displaySpeed(3.12,  100, 300);
									displayKillCount(3,  100, 350);
			}

			break;

		case 0x04:
			if(first_try == 0){
						graphics_clear_screen();
						first_try = 1;
						displayTextBox("YOU WIN!!!", BLUE, CYAN, GREEN);
					}

			break;

		case 0x08:

			if(first_try == 0){
								graphics_clear_screen();
								first_try = 1;
								displayTextBox("GAME OVER", RED, PINK, WHITE);
							}


			break;

		case 0x10:


			break;

		default:

			break;
		}
	}


	//displayLose();
}



