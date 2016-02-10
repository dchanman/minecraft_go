/*
 * general.h
 *
 *  Created on: Jan 14, 2016
 *      Author: derek
 */

#ifndef GENERAL_H_
#define GENERAL_H_

#include <stdio.h>

#define EXIT_OK 0

typedef enum { false, true } bool;

#define DEBUGGING

#ifdef DEBUGGING
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

#endif /* GENERAL_H_ */
