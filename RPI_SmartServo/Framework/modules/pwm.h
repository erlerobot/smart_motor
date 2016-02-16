/*************************************************
** 					        **
** 	project  : 	RPI_SmartServo	        **
** 	filename :	pwm.h			**
** 	version  :	1			**
** 	date     :	9/2/2016		**
** 						**
**************************************************
** 						**
** 	Copyright (c) 2016, Jorge Lampérez	**
** 	All rights reserved.			**
** 						**
**************************************************

VERSION HISTORY:
----------------

Version       : 1
Date          : 9/2/2016
Revised by    : Jorge Lampérez
Description   : 

*/
#ifndef PWM_H_
#define PWM_H_ 1

#include <stdint.h>

// Initialize the PWM module for controlling a DC motor
void PWM_init(void);
// Initialize the PWM algorithm related registers values.
void PWM_registers_defaults(void);
// Update PWM signal sent to the motor -255 to -1 cw,
// 1-255 ccw and 0 stop.
void PWM_update(uint16_t position, int16_t pwm);
// Stop all PWM signals to the motor.
void PWM_stop(void);


#endif
