/*
 * minecraft_rpc.c
 *
 *  Created on: Jan 23, 2016
 *      Author: derek
 */
#include <stdio.h>
#include <string.h>
#include "minecraft_rpc.h"
#include "rs232.h"

#define MINECRAFT_RPC_MSG_LENGTH (3)
/**
 * The messages here need to be added in the same order
 * as they are defined as enums
 */
static const unsigned char * minecraft_rpc_msg_map[] = {
		/* MINECRAFT_RPC_HI */
		(const unsigned char *)("#hi"),
		/* MINECRAFT_RPC_RECV_COORDINATES */
		(const unsigned char *)("#rc"),
		/* MINECRAFT_RPC_JOURNEY_COMPLETE */
		(const unsigned char *)("#jc")
};

void minecraft_rpc_init() {
	rs232_init();
}

int minecraft_rpc_send_cmd(minecraft_rpc_msg_enum_t cmd) {
	unsigned char recv[MINECRAFT_RPC_MSG_LENGTH];
	int i;

	if (cmd > MINECRAFT_RPC_ENUM_MAX) {
		printf("Error: command is outside the enum range\n");
		return 1;
	}

	rs232_put_n_char(minecraft_rpc_msg_map[cmd], MINECRAFT_RPC_MSG_LENGTH);
	rs232_clear_buffer();
	rs232_get_n_char(recv, MINECRAFT_RPC_MSG_LENGTH);

	/* Make sure that the server echoed back the same command we sent */
	for (i = 0; i < MINECRAFT_RPC_MSG_LENGTH; i++) {
		if (recv[i] != minecraft_rpc_msg_map[cmd][i]) {
			printf("Error: Received unexpected message");
			return 1;
		}
	}

	return 0;
}
