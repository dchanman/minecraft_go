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
void block_clear(int x, int y);

/*
 * generates small cracks over a block using the top left coordinate (x, y)
 */
void block_small_crack_generator(int x, int y);

/*
 * generates large cracks over a block using the top left coordinate (x, y)
 */
void block_large_crack_generator(int x, int y);

/*
 * generates a wood block using the top left coordinate (x, y)
 */
void block_wood_generator(int x, int y);

/*
 * generates a grass block using the top left coordinate (x, y)
 */
void block_grass_generator(int x, int y);

/*
 * generates a soil block using the top left coordinate (x, y)
 */
void block_soil_generator(int x, int y);

/*
 * generates a stone block using the top left coordinate (x, y)
 */
void block_stone_generator(int x, int y);

/*
 * generates a iron block using the top left coordinate (x, y)
 */
void block_iron_generator(int x, int y);

/*
 * generates a diamond block using the top left coordinate (x, y)
 */
void block_diamond_generator(int x, int y);

#endif /* BLOCKS_H_ */
