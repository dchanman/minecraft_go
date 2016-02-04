/*
 * minecraft_rpc.h
 *
 *  Created on: Jan 23, 2016
 *      Author: derek
 */

#ifndef MINECRAFT_RPC_H_
#define MINECRAFT_RPC_H_

#include "general.h"

/**
 * Initializes the Minecraft RPC communication link.
 *
 * Call this function prior to reading or writing data to the
 * Minecraft server.
 */
void minecraft_rpc_init();

bool minecraft_rpc_hi();
bool minecraft_rpc_receive_coordinates(char *latitude, const int latitude_length, char *longitude, const int longitude_length);
bool minecraft_rpc_journey_complete(const int elapsed_hours, const int elapsed_min, const int elapsed_sec, const int creep_encs);


#endif /* MINECRAFT_RPC_H_ */

