/**
 *  project  : 	RPI_SmartServo
 *
 * 	@file service.c
 *  @brief State machine for the Server communication.
 *
 *  @note
 *
 *  	none
 *
 *  \code
 *  MODIFICATION HISTORY:
 *
 *  Ver   Who        Date        Changes
 *  ----- ---------- ----------  -------------------------------------
 *  1.00 jlamperez  24/3/2016  First release
 *
 *  \endcode
 *
 *	Copyright (c) 2016, Jorge Lampérez. All rights reserved.
 */
#include <stdio.h>
#include <string.h>
#include "service.h"
#include "rpiservo.h"

/**
 *
 *   State machine to execute in the server side for communication.
 *
 *   @param msg Pointer to a MSG structure.
 *
 *   @return	@todo.
 *
 *   @note		None.
 *
 */
unsigned int SERVICE_execute(MSG *msg) {
	//puts("SERVICE_execute");
	unsigned int ret = 0;

	switch (msg->cmd) {
	case CMD_GET_ID:
		msg->id = RPISERVO_getID();
		//puts("Device type");
		break;
	case CMD_GET_POSITION:
		msg->position = RPISERVO_getPosition();
		//puts("Position");
		break;
	case CMD_GET_TEMP:
		msg->temp = RPISERVO_getTemp();
		//puts("Temp");
		break;
	case CMD_GET_BATTERY:
		msg->battery = RPISERVO_getBattery();
		//puts("Battery");
		break;
	case CMD_GET_CURRENT:
		msg->current = RPISERVO_getCurrent();
		//puts("Current");
		break;
	case CMD_GET_ERROR:
		msg->error = RPISERVO_getError();
		//puts("Error");
		break;
	case CMD_GET_VELOCITY:
		msg->velocity = RPISERVO_getVelocity();
		//puts("Velocity");
		break;
	case CMD_GET_ALL:
		msg->id = RPISERVO_getID();
		msg->position = RPISERVO_getPosition();
		msg->temp = RPISERVO_getTemp();
		msg->battery = RPISERVO_getBattery();
		msg->current = RPISERVO_getCurrent();
		msg->error = RPISERVO_getError();
		msg->velocity = RPISERVO_getVelocity();
		//puts("All");
		break;
	case CMD_GET_PID_CONF:
		msg->p_gain = get_pid_pgain();
		//puts("Pid pgain");
		msg->d_gain = get_pid_dgain();
		//puts("Pid pgain");
		break;
	case CMD_GET_CW_LIMIT:
		msg->cw_limit = RPISERVO_getCWLimit();
		//puts("Pid dgain");
		break;
	case CMD_GET_CCW_LIMIT:
		msg->ccw_limit = RPISERVO_getCCWLimit();
		//puts("Pid igain");
		break;
	case CMD_SET_ID:
		RPISERVO_setID(msg->id);
		//puts("Set id");
		break;
	case CMD_SET_GOAL:
		RPISERVO_setGoal(msg->position);
		//puts("Set Goal");
		break;
	case CMD_SET_CW_LIMIT:
		RPISERVO_setCWLimit(msg->cw_limit);
		//puts("Set cw limit");
		break;
	case CMD_SET_CCW_LIMIT:
		RPISERVO_setCCWLimit(msg->ccw_limit);
		//puts("Set ccw limit");
		break;
	case CMD_SET_PID_CONF:
		RPISERVO_setPIDconf(msg->p_gain, msg->d_gain);
//		set_pid_pgain(msg->p_gain);
		//puts("Set PID pgain");
//		set_pid_dgain(msg->d_gain);
		//puts("Set PID dgain");
		break;
	case CMD_END:				//CMD_END
		//puts("End");
		ret = -1;
		break;
	default:
		break;
	}

	return ret;
}

