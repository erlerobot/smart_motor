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

/**********CMD_GET**************/
#define CMD_GET_ID       		0
#define CMD_GET_POSITION    	1
#define CMD_GET_TEMP			2
#define CMD_GET_BATTERY 		3
#define CMD_GET_CURRENT  	 	4
#define CMD_GET_ERROR    		5
#define CMD_GET_VELOCITY		6
#define CMD_GET_PID_CONF        7
#define CMD_GET_CW_LIMIT        8
#define CMD_GET_CCW_LIMIT       9
#define CMD_GET_ALL             10
/** todo
#define CMD_GET_SEEK_VELOCITY	9
#define CMD_GET_PID_DEADBAND	10
*/
/***********CMD_SET***************/
#define CMD_SET_ID  			30
#define CMD_SET_GOAL         	31
#define CMD_SET_CW_LIMIT        32
#define CMD_SET_CCW_LIMIT       33
#define CMD_SET_PID_CONF        34
/** todo
#define CMD_SET_SEEK_VELOCITY	32
*/
#define CMD_END					60

/**
 *  MSG struct to send between server and client.
 */
typedef struct{
		unsigned char cmd;
		int id;
		float position;
		float temp;
		float battery;
		float current;
		float error;
		float velocity;
		int p_gain;
		int d_gain;
		int cw_limit;
		int ccw_limit;
                int goal;

}MSG;

/**
 *  State machine for server client communication in server side.
 */
unsigned int SERVICE_execute(MSG *msg);

#endif /* SERVICE_H_ */
