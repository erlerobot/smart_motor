/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file main.c
 *  @brief main file
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

/* 
	#include modules
*/
#include <wiringPi.h>	
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "Framework/modules/pwm.h"
#include "Framework/modules/registers.h"
#include "Framework/modules/pid.h"
#include "Framework/modules/adc.h"
#include "Framework/modules/timer.h"
#include "Framework/modules/server.h"
#include "config.h"

void createServer();//Creates the server thread to recive commands via TCP/IP
void* serverThread(void*);

int main(void)
{
	printf("Smart Servo\n");
// MODULE INITIALIZATION

	// This initialises the wiringPi system and 
	// assumes that the calling program is going 
	// to be using the Broadcom GPIO pin numbers directly.
	wiringPiSetupGpio();
	// Configure pins to the default states

	// First, initialize registers that control servo operation
	// Set the initial seek position and velocity
	REGISTERS_init();
	// Initialize the PWM module
	PWM_init();
	// Initialize ADC module
	ADC_init();
	// Initialize the PID algorithm module
	PID_init();
	// Initialize timer 10 ms.
	TIMER_init(CONFIG_TIMER);
//MODULE INITIALIZATION END
	
	//Create Server thread for communication
	createServer();

	// Main processing loop for the servo. It basically 
	// looks for new position, power or TWI commands to 
	// be processed.
	for(;;)
	{	
		
		static int i=0;
		if(adc_position_value_is_ready())
		{   printf("Time: %f seconds\n", (double)clock() /CLOCKS_PER_SEC);
		    
		    // Is position value ready?
            clock_t tic = clock();
			int16_t pwm;
			int16_t position;
			
			/** @todo */
			// get position() better ??
			position = adc_get_position_value();

			// Call the PID algorithm module to get a new PWM value. 
			pwm = PID_position_to_pwm(position);

			// Update the servo movement as indicated by the PWM value.
			PWM_update(position, pwm);
                        printf("MAIN position value is: %d \n", position);
			printf("MAIN pwm value is: %d \n", pwm);
			printf("------------%i--------------\n",i);
			i++;
			clock_t toc = clock();
		    printf("Elapsed: %f seconds\n", (double)(toc-tic) /CLOCKS_PER_SEC);
		}
		// Is a power value ready?

			// Get the new power value.

			// Update the power value for reporting.

		// Was a command received?

			// handle twi command
	}
}

void createServer(){
	pthread_t thread_id;
	if (pthread_create(&thread_id, NULL, serverThread, 0) < 0) {
		perror("could not create the server thread");
	}
}

void *serverThread(void *server_desc){
	SERVER_init();
	return 0;
}
