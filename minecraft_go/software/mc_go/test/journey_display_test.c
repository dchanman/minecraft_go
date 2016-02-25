/*
 * journey_display.c
 *
 *  Created on: 2016-02-23
 *      Author: Johnson
 */

#include <unistd.h>
#include "general.h"
#include "journey_display.h"
#include "graphics.h"

void journey_display_test(){

	Time time1 = {21, 45, 22};

	graphics_clear_screen();
	displayElapsedTime(&time1, 100, 100);
	displayDestDistance(54.35, 100, 150);
	displaySpeed(3.12,  100, 200);
}



