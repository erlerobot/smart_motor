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
#include "registers.h"


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
	case CMD_GET_DEVICE_TYPE:
		msg->value = get_device_type();
		//puts("Device type");
		break;
	case CMD_GET_DEVICE_SUBTYPE:
		msg->value = get_device_subtype();
		//puts("Device subtype");
		break;
	case CMD_GET_FLAGS:
		msg->value = get_flags();
		//puts("Flags");
		break;
	case CMD_GET_POSITION:
		msg->value = get_position();
		//puts("Position");
		break;
	case CMD_GET_VELOCITY:
		msg->value = get_velocity();
		//puts("Velocity");
		break;
	case CMD_GET_PWM_DIR_A:
		msg->value = get_pwm_dir_a();
		//puts("PWM dir a");
		break;
	case CMD_GET_PWM_DIR_B:
		msg->value = get_pwm_dir_b();
		//puts("PWM dir b");
		break;
	case CMD_GET_SEEK_POSITION:
		msg->value = get_seek_position();
		//puts("Seek position");
		break;
	case CMD_GET_SEEK_VELOCITY:
		msg->value = get_seek_velocity();
		//puts("Seek velocity");
		break;
	case CMD_GET_TEMP:
		msg->value = get_temp();
		//puts("Voltage");
		break;
	case CMD_GET_PID_DEADBAND:
		msg->value = get_pid_deadband();
		//puts("Pid deadband");
		break;
	case CMD_GET_PID_PGAIN:
		msg->value = get_pid_pgain();
		//puts("Pid pgain");
		break;
	case CMD_GET_PID_DGAIN:
		msg->value = get_pid_dgain();
		//puts("Pid dgain");
		break;
	case CMD_GET_PID_IGAIN:
		msg->value = get_pid_igain();
		//puts("Pid igain");
		break;
	case CMD_GET_MIN_SEEK:
		msg->value = get_min_seek();
		//puts("Min Seek");
		break;
	case CMD_GET_MAX_SEEK:
		msg->value = get_max_seek();
		//puts("Max Seek");
		break;
	case CMD_GET_ALL:
		//puts("Get all");
		break;
	case CMD_SET_FLAGS:
		set_flags(msg->value);
		//puts("Set flags");
		break;
	case CMD_SET_SEEK_POSITION:
		set_seek_position(msg->value);
		//puts("Set Seek position");
		break;
	case CMD_SET_SEEK_VELOCITY:
		set_seek_velocity(msg->value);
		//puts("Set seek velocity");
		break;
	case CMD_SET_PID_DEADBAND:
		set_pid_deadband(msg->value);
		//puts("Set PID deadband");
		break;
	case CMD_SET_PID_PGAIN:
		set_pid_pgain(msg->value);
		//puts("Set PID pgain");
		break;
	case CMD_SET_PID_IGAIN:
		set_pid_igain(msg->value);
		//puts("Set PID igain");
		break;
	case CMD_SET_PID_DGAIN:
		set_pid_dgain(msg->value);
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

