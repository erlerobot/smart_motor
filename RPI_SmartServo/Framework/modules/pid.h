/*************************************************
** 						**
** 	project  : 	RPI_SmartServo		**
** 	filename :	pid.h			**
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

#ifndef PID_H_
#define PID_H_ 1

#include<stdint.h>

// Initialize the pid algorithm module.
void PID_init(void);

// Initialize the pid related registers.
void PID_registers_default(void);

// Take position as input(0-1024) and output assigned PWM 
// to be applied to the servo motors.
int16_t PID_position_to_pwm(int16_t current_position);


#endif
