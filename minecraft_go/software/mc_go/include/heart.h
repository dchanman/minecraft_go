/*
 * heart.h
 *
 *  Created on: February 13, 2016
 *  Updated on: February 13, 2016
 *      Author: Logan
 */

#ifndef HEART_H_
#define HEART_H_

/*
 * Draws a heart
 * x - top left x coordinate
 * y - top left y coordinate
 * width - width of the base of the creeper
 */
void heart_draw(int x, int y, int width);

/*
 * Erases a heart
 * x - top left x coordinate
 * y - top left y coordinate
 * width - width of the base of the creeper
 */
void heart_erase(int x, int y, int width);

#endif /* HEART_H_ */
