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
void displayKillCount(int creeper_kill, int start_x_coord, int y_coord);
void displayMenu(Time *time1, double distance, float speed, int kill_count);
void displayFight();
void displaySmash();
void displayWin();
void displayLose();
void displayTextBox(char* text, int text_color, int border_color, int box_color);
void displayTouchPrompt();
void displayBackground();

#endif /* JOURNEY_DISPLAY_H_ */
