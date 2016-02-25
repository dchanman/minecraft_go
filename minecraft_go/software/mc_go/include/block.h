/*
 * block.h
 *
 *  Created on: February 10, 2016
 *  Updated on: February 10, 2016
 *      Author: Logan
 */

#ifndef BLOCKS_H_
#define BLOCKS_H_

/*
 * clears a block using the top left coordinate (x, y)
 */
void clear_block(int x, int y);

void soil_block_generator(int x, int y);

void grass_block_generator(int x, int y);

/*
 * generates a wood block using the top left coordinate (x, y)
 */
void wood_block_generator(int x, int y);

/*
 * generates a stone block using the top left coordinate (x, y)
 */
void stone_block_generator(int x, int y);

/*
 * generates a iron block using the top left coordinate (x, y)
 */
void iron_block_generator(int x, int y);

/*
 * generates a diamond block using the top left coordinate (x, y)
 */
void diamond_block_generator(int x, int y);

#endif /* BLOCKS_H_ */
