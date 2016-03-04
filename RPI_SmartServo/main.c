/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file main.c
 *  @brief 
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
 *  1.00 jlamperez  1/3/2016  First release
 * 
 *  \endcode
 *
 *	Copyright (c) 2016, Jorge Lampérez. All rights reserved.
 */

/* 
	#include modules
*/
#include <wiringPi.h>	
#include <stdint.h>
#include <stdio.h>
#include "Framework/modules/pwm.h"
#include "Framework/modules/registers.h"
#include "Framework/modules/pid.h"
#include "Framework/modules/adc.h"
#include "Framework/modules/timer.h"

int main(void)
{

// MODULE INITIALIZATION

	// This initialises the wiringPi system and 
	//assumes that the calling program is going 
	//to be using the Broadcom GPIO pin numbers directly.
	wiringPiSetupGpio();
	// Configure pins to the default states

	// First, initialize registers that control servo operation
	REGISTERS_init();
	// Initialize the PWM module
	PWM_init();
	// Initialize the ADC module

	// Initialize the PID algorithm module
	PID_init();
	// Initialize ADC
	ADC_init();
	// Initialize timer 10 ms.
	TIMER_init(10000);
//MODULE INITIALIZATION END

	// Set the initial seek position and velocity

	// XXX Enable PWM and writing.


	// Main processing loop for the servo. It basically 
	// looks for new position, power or TWI commands to 
	// be processed.
	printf("Insert new seek_position: \n"); 
        int16_t seek_position;
	scanf("%hd",&seek_position); 
	set_seek_position(seek_position);
	
	for(;;)
	{	
		// Is position value ready?
			int16_t pwm;
			int16_t position;
			
			// Get the new position value.
			printf("Insert new position: \n"); 
			scanf("%hd",&position); 
			printf("New position value is: %d \n", position); 
				
				// Call the PID algorithm module to get a new PWM value. 
				pwm = PID_position_to_pwm(position);
				printf("PWM value is: %d \n", pwm); 
				// Update the servo movement as indicated by the PWM value.
				PWM_update(position, pwm);

		// Is a power value ready?

			// Get the new power value.

			// Update the power value for reporting.

		// Was a command received?

			// handle twi command
	}
}
