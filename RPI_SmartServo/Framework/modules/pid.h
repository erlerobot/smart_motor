/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file pid.h
 *  @brief Header for PID module implementation
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
 *  1.00 jlamperez  6/3/2016  First release
 * 
 *  \endcode
 *
 *	Copyright (c) 2016, Jorge Lampérez. All rights reserved.
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
