/*
 * sprint1_demo.c
 *
 *  Created on: Feb 2, 0216
 *      Author: derek
 */

#include "stdio.h"
#include "hw.h"
#include "test.h"

void sprint1_demo() {
	printf("===========================================\n");
	printf("%s:\n", __func__);

	char switch_val = hw_switches_get();

	switch(switch_val) {
	case 0x00:
		printf("Touchscreen Demo\n", switch_val);
		touchscreen_test();
		break;
	case 0x01:
		printf("Minecraft RPC Demo\n", switch_val);
		minecraft_rpc_test_protocol_msg();
		break;
	case 0x02:
		printf("GPS Demo\n", switch_val);
		gps_test();
		break;
	case 0x03:
		printf("Graphics Demo\n", switch_val);
		break;
	default:
		printf("No demo available for val <0x%02x>", switch_val);
		break;
	}

	printf("Demo Done\n");
}



