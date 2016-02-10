/*
 * minigames.h
 *
 *  Created on: Feb 9, 2016
 *  Updated on: Feb 9, 2016
 *      Author: Derek
 */

#ifndef MINIGAMES_H_
#define MINIGAMES_H_

#include "general.h"

/*
 * type declaration for grid boxes
 * x - top left x coordinate
 * y - top left y coordinate
 */
typedef struct {
    int x;
    int y;
    int health;
} Box;

/**************************************************************************
 * Digging Minigame Functions
 **************************************************************************/
/*
 * Starts the digging minigame.
 * @return true when the game completes, false if the player didn't complete the game
 */
bool digging_minigame_play();


/**************************************************************************
 * Creeper Encounter Minigame Functions
 **************************************************************************/
/*
 *
 */
bool minigame_creep_encounter(int *player_heath);


#endif /* MINIGAMES_H_ */
