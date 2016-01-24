/*
 * minecraft_rpc.h
 *
 *  Created on: Jan 23, 2016
 *      Author: derek
 */

#ifndef MINECRAFT_RPC_H_
#define MINECRAFT_RPC_H_

/**
 * The message strings are implemented in minecraft_rpc.c.
 * If you add an enum here, add it to the map in the C file as well!
 */
typedef enum {
	MINECRAFT_RPC_HI = 0,
	MINECRAFT_RPC_RECV_COORDINATES,
	MINECRAFT_RPC_JOURNEY_COMPLETE,
	MINECRAFT_RPC_ENUM_MAX
} minecraft_rpc_msg_enum_t;

/**
 * Initializes the Minecraft RPC communication link.
 *
 * Call this function prior to reading or writing data to the
 * Minecraft server.
 */
void minecraft_rpc_init();

/**
 * Sends a command to the Minecraft server
 */
int minecraft_rpc_send_cmd(minecraft_rpc_msg_enum_t cmd);

#endif /* MINECRAFT_RPC_H_ */

