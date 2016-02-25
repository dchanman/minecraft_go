/*
 *  journey_display.c
 *
 *  Created on: 2016-02-23
 *      Author: Johnson
 */

#include <stdint.h>
#include <stdio.h>
#include "journey_display.h"
#include "block.h"
#include "graphics.h"
#include "gps.h"
#include "Colours.h"



void displayElapsedTime(Time *elapsedTime, int start_x_coord, int y_coord){
	char buffer[100];

	sprintf(buffer, "Elapsed Time: %dhr %dmin %dsec", elapsedTime->hour, elapsedTime->minute, elapsedTime->second);

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont4(start_x_coord + i*13, y_coord, RED, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
}

void displayDestDistance(double dist_km,  int start_x_coord, int y_coord){
	char buffer[100];

	sprintf(buffer, "Destination Distance: %.2fkm", dist_km);

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont4(start_x_coord + i*13, y_coord, RED, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
}

void displaySpeed(float speed_km_h,  int start_x_coord, int y_coord){
	char buffer[100];

	sprintf(buffer, "Current Speed: %.2fkm/h", speed_km_h);

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont4(start_x_coord + i*13, y_coord, RED, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
}

void displayKillCount(int creeper_kill,  int start_x_coord, int y_coord){
	char buffer[100];

	sprintf(buffer, "Creepers Killed: %d", creeper_kill);

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont4(start_x_coord + i*13, y_coord, RED, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
}

void displayMenu(  int start_x_coord, int y_coord){
	char buffer[100];

	sprintf(buffer, "Minecraft GO");



	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont5(start_x_coord + i*32, y_coord, WHITE, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
	HLine(start_x_coord, y_coord+55, start_x_coord+9*32, WHITE);
}

void displayFight(){
	char buffer[100];

	graphics_draw_rectangle_filled(225, 150, 11*32, 200, WHITE);
	graphics_draw_rectangle_border(225, 150, 11*32, 200, BLACK);

	sprintf(buffer, "FIGHT!!!!");

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont5(250 + i*32, 225, GREEN, GRAPHICS_BACKGROUND_COLOUR , buffer[i], FALSE);
		i++;
	}
}

void displaySmash(){
	char buffer[100];

	graphics_draw_rectangle_filled(225, 150, 11*32, 200, WHITE);
	graphics_draw_rectangle_border(225, 150, 11*32, 200, BLACK);

	sprintf(buffer, "SMASH!!!!");

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont5(250 + i*32, 225, GREEN, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
}

void displayWin(){
	char buffer[100];

	graphics_draw_rectangle_filled(225, 150, 11*32, 200, WHITE);
	graphics_draw_rectangle_border(225, 150, 11*32, 200, BLACK);

	sprintf(buffer, "YOU WIN!!!");

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont5(250 + i*32, 225, GREEN, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
}

void displayLose(){
	char buffer[100];

	graphics_draw_rectangle_filled(225, 150, 11*32, 200, WHITE);
	graphics_draw_rectangle_border(225, 150, 11*32, 200, BLACK);

	sprintf(buffer, "GAME OVER");

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont5(250 + i*32, 225, RED, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
}

void displayTextBox(char* text, int text_color, int border_color, int box_color){
	char buffer[100];

	graphics_draw_rectangle_filled(225, 150, 12*32, 200, box_color);
	graphics_draw_rectangle_border(225, 150, 12*32, 200, border_color);

	sprintf(buffer, text);

	int i = 0;

	while(buffer[i]){
		printf("%c", buffer[i]);
		OutGraphicsCharFont5(250 + i*32, 225, text_color, GRAPHICS_BACKGROUND_COLOUR , buffer[i], TRUE);
		i++;
	}
}

void displayBackground(){

	int i;
	for(i = 0; i < 3; i++){
		soil_block_generator(i*240, 240);
		grass_block_generator(i*240,0);
	}

	soil_block_generator(560, 240);
	grass_block_generator(560,0);


}


