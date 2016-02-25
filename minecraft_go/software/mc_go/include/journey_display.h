/*
 * journey_display.h
 *
 *  Created on: 2016-02-23
 *      Author: Johnson
 */

#ifndef JOURNEY_DISPLAY_H_
#define JOURNEY_DISPLAY_H_

#include "general.h"

void displayElapsedTime(Time *elapsedTime, int start_x_coord, int y_coord);
void displayDestDistance(double dist_km,  int start_x_coord, int y_coord);
void displaySpeed(float speed_km_h,  int start_x_coord, int y_coord);




#endif /* JOURNEY_DISPLAY_H_ */
