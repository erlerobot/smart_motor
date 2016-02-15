/*
	main.c
*/

/* 
	#include modules
*/
#include <wiringPi.h>	
#include "pwm.h"
#include "registers.h"
#include "pid.h"

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
	// Initialize the curve motion module

	// Initialize the power module

	// Initialize pulse control

	// Initialize software I2C to talk with encoder

	// Initialize the TWI slave module

//MODULE INITIALIZATION END

	// Set the initial seek position and velocity

	// XXX Enable PWM and writing.


	// Main processing loop for the servo. It basically 
	// looks for new position, power or TWI commands to 
	// be processed.
	for(;;)
	{	
		// Is position value ready?

			// Get the new position value.

			// Call the PID algorithm module to get a new PWM value. 

			// Update the servo movement as indicated by the PWM value.


		// Is a power value ready?

			// Get the new power value.

			// Update the power value for reporting.

		// Was a command received?

			// handle twi command
	}
}