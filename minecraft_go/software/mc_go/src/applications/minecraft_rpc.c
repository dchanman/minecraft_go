/*
 * minecraft_rpc.c
 *
 *  Created on: Jan 23, 2016
 *      Author: derek
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "minecraft_rpc.h"
#include "rs232.h"

#define MINECRAFT_RPC_MSG_LENGTH (3)

typedef enum {
	MINECRAFT_RPC_HI = 0,
	MINECRAFT_RPC_RECV_COORDINATES,
	MINECRAFT_RPC_JOURNEY_COMPLETE,
	MINECRAFT_RPC_ENUM_MAX
} minecraft_rpc_msg_enum_t;

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

/* Static function declarations */

static boolean minecraft_rpc_send_and_check(const unsigned char *message, const int length) {
	unsigned char recv[length];
	int i;

	rs232_clear_buffer();
	rs232_put_n_char(message, length);
	rs232_get_n_char(recv, length);

	/* Make sure that the server echoed back the same command we sent */
	for (i = 0; i < length; i++) {
		if (recv[i] != message[i]) {
			printf("Error: Received unexpected message <%.*s>\n", length, message);
			return FALSE;
		}
	}

	return TRUE;
}

static boolean minecraft_rpc_receive_and_echo(unsigned char *message, const int length) {
	/* Receive */
	rs232_get_n_char(message, length);

	/* Echo */
	rs232_put_n_char(message, length);

	return TRUE;
}

static boolean minecraft_rpc_send_cmd(minecraft_rpc_msg_enum_t cmd) {
	if (cmd > MINECRAFT_RPC_ENUM_MAX) {
		printf("Error: command is outside the enum range\n");
		return FALSE;
	}

	return minecraft_rpc_send_and_check(minecraft_rpc_msg_map[cmd], MINECRAFT_RPC_MSG_LENGTH);
}

void minecraft_rpc_init() {
	rs232_init();
}

boolean minecraft_rpc_hi() {
	/* Send #hi */
	if (!minecraft_rpc_send_cmd(MINECRAFT_RPC_HI)) {
		printf("Error: Connection handshake failed\n");
		return FALSE;
	}

	return TRUE;
}

boolean minecraft_rpc_receive_coordinates(Location *location)
{
	unsigned char buffer[16];

	/* Validate Inputs */
	if (location == NULL) {
		printf("Error: location was NULL\n");
		return FALSE;
	}

	/* Send #rc to connect */
	if (!minecraft_rpc_send_cmd(MINECRAFT_RPC_RECV_COORDINATES)) {
		printf("Error: Connection handshake failed\n");
		return FALSE;
	}

	/* Get lat_minute */
	DEBUG("[%s]: Getting lat_minute...\n", __func__);
	memset(buffer, '\0', sizeof(buffer));
	if (!minecraft_rpc_receive_and_echo(buffer, 7)) {
		printf("Error: Problem receiving lat_minute");
		return FALSE;
	}
	location->lat_minute = atof(buffer);
	DEBUG("[%s]: Received lat_minute: <%lf>\n", __func__, location->lat_minute);

	/* Get lat_degree */
	DEBUG("[%s]: Getting lat_degree...\n", __func__);
	memset(buffer, '\0', sizeof(buffer));
	if (!minecraft_rpc_receive_and_echo(buffer, 2)) {
		printf("Error: Problem receiving lat_degree");
		return FALSE;
	}
	location->lat_degree = atoi(buffer);
	DEBUG("[%s]: Received lat_degree: <%d>\n", __func__, location->lat_degree);

	/* Get lat_direction */
	DEBUG("[%s]: Getting lat_direction...\n", __func__);
	memset(buffer, '\0', sizeof(buffer));
	if (!minecraft_rpc_receive_and_echo(buffer, 1)) {
		printf("Error: Problem receiving lat_direction");
		return FALSE;
	}
	location->lat_direction = (char)buffer[0];
	DEBUG("[%s]: Received lat_direction: <%c>\n", __func__, location->lat_direction);

	/* Get long_minute */
	DEBUG("[%s]: Getting long_minute...\n", __func__);
	memset(buffer, '\0', sizeof(buffer));
	if (!minecraft_rpc_receive_and_echo(buffer, 7)) {
		printf("Error: Problem receiving long_minute");
		return FALSE;
	}
	location->long_minute = atof(buffer);
	DEBUG("[%s]: Received long_minute: <%lf>\n", __func__, location->long_minute);

	/* Get long_degree */
	DEBUG("[%s]: Getting long_degree...\n", __func__);
	memset(buffer, '\0', sizeof(buffer));
	if (!minecraft_rpc_receive_and_echo(buffer, 3)) {
		printf("Error: Problem receiving long_degree");
		return FALSE;
	}
	location->long_degree = atoi(buffer);
	DEBUG("[%s]: Received long_degree: <%d>\n", __func__, location->long_degree);

	/* Get long_direction */
	DEBUG("[%s]: Getting long_direction...\n", __func__);
	memset(buffer, '\0', sizeof(buffer));
	if (!minecraft_rpc_receive_and_echo(buffer, 1)) {
		printf("Error: Problem receiving long_direction");
		return FALSE;
	}
	location->long_direction = (char)buffer[0];
	DEBUG("[%s]: Received long_direction: <%c>\n", __func__, location->long_direction);


	/* Send #rc to close */
	if (!minecraft_rpc_send_cmd(MINECRAFT_RPC_RECV_COORDINATES)) {
		printf("Error: Close handshake failed\n");
		return FALSE;
	}

	return TRUE;
}

boolean minecraft_rpc_journey_complete(const int elapsed_hours, const int elapsed_min, const int elapsed_sec, const int creep_encs)
{
	unsigned char elapsed_time_buffer[10] = {'\0'};
	unsigned char creep_encs_buffer[4] = {'\0'};

//	/* Validate Inputs */
//	if (elapsed_hours > 1000 || elapsed_min > 100 || elapsed_sec > 100 || creep_encs > 1000) {
//		printf("Error: Invalid input parameters: hhh: <%03d> mm:<%02d> ss:<%02d> creep_encs:<%02d>\n",
//				elapsed_hours, elapsed_min, elapsed_sec, creep_encs);
//		return FALSE;
//	}

	/* Send #rc to connect */
	if (!minecraft_rpc_send_cmd(MINECRAFT_RPC_JOURNEY_COMPLETE)) {
		printf("Error: Connection handshake failed\n");
		return FALSE;
	}

	/* Create the buffers */
	snprintf((char *)(elapsed_time_buffer), sizeof(elapsed_time_buffer), "%03d:%02d:%02d",
			elapsed_hours, elapsed_min, elapsed_sec);
	snprintf((char *)(creep_encs_buffer), sizeof(creep_encs_buffer), "%03d", creep_encs);

	/* Send Elapsed Time */
	/* (sizeof(buffer)-1 because we don't send the \0 char */
	DEBUG("[%s]: Sending elapsed time <%s>\n", __func__, elapsed_time_buffer);
	if (!minecraft_rpc_send_and_check(elapsed_time_buffer, sizeof(elapsed_time_buffer) - 1)) {
		printf("Error: Could not send elapsed time\n");
		return FALSE;
	}

	/* Send Creep Encs */
	/* (sizeof(buffer)-1 because we don't send the \0 char */
	DEBUG("[%s]: Sending creep encounters <%s>\n", __func__, creep_encs_buffer);
	if (!minecraft_rpc_send_and_check(creep_encs_buffer, sizeof(creep_encs_buffer) - 1)) {
		printf("Error: Could not send creep encounters\n");
		return FALSE;
	}

	/* Send #rc to close */
	if (!minecraft_rpc_send_cmd(MINECRAFT_RPC_JOURNEY_COMPLETE)) {
		printf("Error: Close handshake failed\n");
		return FALSE;
	}

	return TRUE;
}
