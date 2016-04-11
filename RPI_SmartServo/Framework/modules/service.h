/**
 *  project  : 	RPI_SmartServo
 *
 * 	@file service.h
 *  @brief Header for service module.
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

#ifndef SERVICE_H_
#define SERVICE_H_

#include<stdint.h>

/**********CMD_GET**************/
#define CMD_GET_DEVICE_TYPE		0
#define CMD_GET_DEVICE_SUBTYPE	1
#define CMD_GET_FLAGS			2
#define CMD_GET_POSITION		3
#define CMD_GET_VELOCITY	 	4
#define CMD_GET_PWM_DIR_A		5
#define CMD_GET_PWM_DIR_B		6
#define CMD_GET_SEEK_POSITION	7
#define CMD_GET_SEEK_VELOCITY	8
#define CMD_GET_TEMP			9
#define CMD_GET_PID_DEADBAND	10
#define CMD_GET_PID_PGAIN		11
#define CMD_GET_PID_IGAIN		12
#define CMD_GET_PID_DGAIN		13
#define CMD_GET_MIN_SEEK		14
#define CMD_GET_MAX_SEEK		15
#define CMD_GET_ALL				16
/***********CMD_SET***************/
#define CMD_SET_FLAGS 			30
#define CMD_SET_SEEK_POSITION	31
#define CMD_SET_SEEK_VELOCITY	32
#define CMD_SET_PID_DEADBAND	33
#define CMD_SET_PID_PGAIN		34
#define CMD_SET_PID_IGAIN		35
#define CMD_SET_PID_DGAIN		36

#define CMD_END					60

/**
 *  MSG struct to send between server and client.
 */
typedef struct{
		unsigned char cmd;
		uint16_t value;

}MSG;

/**
 *  State machine for server client communication in server side.
 */
unsigned int SERVICE_execute(MSG *msg);

#endif /* SERVICE_H_ */
