/*
 *  touchscreen.h
 *
 *  Created on: January 24, 2016
 *      Author: Logan
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

/* a data type to hold a point/coord */
typedef struct { int x, y; } Point ;

/*****************************************************************************
** Initialise touch screen controller
*****************************************************************************/
void init_touchscreen(void);

/*****************************************************************************
** test if screen touched
*****************************************************************************/
void screen_touched( void );

/*****************************************************************************
** wait for screen to be touched
*****************************************************************************/
void wait_for_touch();

/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*****************************************************************************/
Point get_press(void);

/*****************************************************************************
* This function waits for a touch screen release event and returns X,Y coord
*****************************************************************************/
Point get_release(void);

#endif /* TOUCHSCREEN_H_ */
