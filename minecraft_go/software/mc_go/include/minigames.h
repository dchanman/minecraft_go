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

typedef enum block_type {
	BLOCK_TYPE_DEAD = 0,
	BLOCK_TYPE_WOOD,
	BLOCK_TYPE_STONE,
	BLOCK_TYPE_IRON,
	BLOCK_TYPE_DIAMOND,
	BLOCK_TYPE_NUM_TYPES /* This must always be the last enum on the list! */
} block_type_t;

/*
 * type declaration for grid boxes
 * x - top left x coordinate
 * y - top left y coordinate
 */
typedef struct {
    int x;
    int y;
    int health;
    int block_type;
} Box;

/**************************************************************************
 * Digging Minigame Functions
 **************************************************************************/
/*
 * Starts the digging minigame.
 * @return true when the game completes, false if the player didn't complete the game
 */
boolean minigame_digging();


/**************************************************************************
 * Creeper Encounter Minigame Functions
 **************************************************************************/
/*
 *
 */
boolean minigame_creeper_encounter(int *player_heath);


#endif /* MINIGAMES_H_ */
