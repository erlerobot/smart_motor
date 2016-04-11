/**
 *  project  : 	RPI_SmartServo
 *
 * 	@file rpiservo.h
 *  @brief Header for rpiservo module, interface for communication.
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
 *  1.00 jlamperez  10/4/2016  First release
 *
 *  \endcode
 *
 *	Copyright (c) 2016, Jorge Lampérez. All rights reserved.
 */
#ifndef FRAMEWORK_MODULES_RPISERVO_H_
#define FRAMEWORK_MODULES_RPISERVO_H_

void RPISERVO_setID(int device_type);
void RPISERVO_setGoal(int degrees);
void RPISERVO_setCWLimit(int degrees);
void RPISERVO_setCCWLimit(int degrees);
void RPISERVO_setPIDconf(int pgain, int dgain, int igain);

int RPISERVO_getID();
float RPISERVO_getPosition();
float RPISERVO_getTemp();
float RPISERVO_getBattery();
float RPISERVO_getCurrent();
float RPISERVO_getError();
float RPISERVO_getVelocity();


#endif /* FRAMEWORK_MODULES_RPISERVO_H_ */
