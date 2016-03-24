/**
 *  project  :  RPI_SmartServo          
 *  
 *  @file pwm.c
 *  @brief Implementation for pwm module.
 * 
 *  @note 
 *
 *      none
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
 *  Copyright (c) 2016, Jorge Lampérez. All rights reserved.
 */


#include <stdint.h> 
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include "../../config.h"
#include "pwm.h"
#include "registers.h"

//Convert the [-255 ,255] to a value between 0 and PWM_RANGE
#define PWM_DUTY_CYCLE(div,pwm) (uint16_t) (((uint32_t) pwm * ((uint32_t) div  - 1)) / 255)

// Flags that indicate PWM output in A and B direction.
static uint8_t pwm_a;
static uint8_t pwm_b;


/*
	Private Functions.
*/
/**
*
*   Send PWM signal for rotation with the indicated pwm ratio (0 - 255).
*   This function is meant to be called only by pwm_update.
*
*   @param      pwm_duty the value of the pwm duty.
*
*   @return	    None.
*
*   @note		pwm_duty.
*
*/
static void pwm_dir_a(uint8_t pwm_duty)
{
    // Determine the duty cycle value for the timer.
    uint16_t duty_cycle = PWM_DUTY_CYCLE(CONFIG_PWM_RANGE, pwm_duty);
    printf("PWM_dir_a_duty_cycle %d \n",duty_cycle);

    // Do we need to reconfigure PWM output for direction A?
    if (!pwm_a)
    { // Yes ..

    	// Disable EN_B_GPIO
        digitalWrite(CONFIG_EN_B_GPIO,0);

    	// Disable PWM0 and PWM1 output.
        pwmWrite(CONFIG_PWM1_GPIO,0);
        pwmWrite(CONFIG_PWM0_GPIO,0);
        delayMicroseconds(CONFIG_PWM_DIR_CHANGE_DELAY);


    	// Set EN_A_GPIO to high.
        digitalWrite(CONFIG_EN_A_GPIO,1);

    	// Reset the B direction flag.
        pwm_b = 0;
    }

    // Update the A direction flag.  A non-zero value keeps us from
    // recofiguring the PWM output A when it is already configured.
    pwm_a = pwm_duty;

    // Update the PWM duty cycle.
    pwmWrite(CONFIG_PWM0_GPIO,duty_cycle);

    // Save the pwm A and B duty values. ??
}
/**
*
*   Send PWM signal for rotation with the indicated pwm ratio (0 - 255).
*   This function is meant to be called only by pwm_update.
*
*   @param      pwm_duty the value of the pwm duty.
*
*   @return	    None.
*
*   @note	    pwm_duty.
*
**/
static void pwm_dir_b(uint8_t pwm_duty)
{
	// Determine the duty cycle value for the timer.
    uint16_t duty_cycle = PWM_DUTY_CYCLE(CONFIG_PWM_RANGE, pwm_duty);
    printf("PWM_dir_b_duty_cycle %d \n",duty_cycle);

        // Do we need to reconfigure PWM output for direction B?
    if (!pwm_b)
    { // Yes ..

    	// Disable EN_A_GPIO
        digitalWrite(CONFIG_EN_A_GPIO,0);
    	// Disable PWM0 and PWM0 output.
    	pwmWrite(CONFIG_PWM0_GPIO,0);
        pwmWrite(CONFIG_PWM1_GPIO,0);
        delayMicroseconds(CONFIG_PWM_DIR_CHANGE_DELAY);

    	// Set EN_B_GPIO to high.
        digitalWrite(CONFIG_EN_B_GPIO,1);
    	// Reset the A direction flag.
        pwm_a = 0;
    }

    // Update the A direction flag.  A non-zero value keeps us from
    // recofiguring the PWM output A when it is already configured.
    pwm_b = pwm_duty;

    // Update the PWM duty cycle.
    pwmWrite(CONFIG_PWM1_GPIO,duty_cycle);

    // Save the pwm A and B duty values. ??
}


/**
*
*   Initialize the PWM module for controlling a DC motor
*
*   @return	    None.
*
*   @note		None.
*
*/
void PWM_init(void)
{	// Initialize the pwm frequency divider value.
	//[TODO]
	

	//Enable PMW0/GPIO12
	pinMode(CONFIG_PWM0_GPIO, PWM_OUTPUT);
	// Set PWM in mark-space mode
	pwmSetMode(PWM_MODE_MS);
	// Divide the RPI PWM clock base frequency(19.2e6) by 2
	pwmSetClock(CONFIG_PWM_CLOCK_DIV);
	// Set the PWM range
	pwmSetRange(CONFIG_PWM_RANGE);
	// Initialize PWM signal to 0.
	pwmWrite(CONFIG_PWM0_GPIO,0);

	//Enable PWM1/GPIO13
	pinMode(CONFIG_PWM1_GPIO, PWM_OUTPUT);
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(CONFIG_PWM_CLOCK_DIV);
	pwmSetRange(CONFIG_PWM_RANGE);
	pwmWrite(CONFIG_PWM1_GPIO,0);

    // Set EN_A (GPIO 16) and EN_B (GPIO 19) to output
    pinMode(CONFIG_EN_A_GPIO, OUTPUT);
    pinMode(CONFIG_EN_B_GPIO,OUTPUT);
    // Set EN_A and EN_B to low.
    digitalWrite(CONFIG_EN_A_GPIO, 0);
    digitalWrite(CONFIG_EN_B_GPIO, 0);

	// Update the pwm values

}

/**
*
*   Update PWM signal sent to the motor -255 to -1 cw,
*   1-255 ccw and 0 stop.
*
*   @param      position current position of the potentiometer. 
*   @param      pwm pwm value to update.
*
*   @return	    None.
*
*   @note		input position and pwm value.
*
*/
void PWM_update(uint16_t position, int16_t pwm)
{
    uint8_t pwm_width;
    uint16_t min_position;
    uint16_t max_position;

    // Get the minimum and maximum seek position.
    min_position = get_min_seek();
    max_position = get_max_seek();

	// Make sure these values are sane 10-bit values.
    if (min_position > CONFIG_PWM_MAX_POSITION) min_position = CONFIG_PWM_MAX_POSITION;
    if (max_position > CONFIG_PWM_MAX_POSITION) max_position = CONFIG_PWM_MAX_POSITION;
    printf("PWM_update_min_position %d \n",min_position);
    printf("PWM_update_max_position %d \n",max_position);
    
    // Disable clockwise movements when position is below the minimum position.
    if ((position < min_position) && (pwm < 0)) pwm = 0;

    // Disable counter-clockwise movements when position is above the maximum position.
    if ((position > max_position) && (pwm > 0)) pwm = 0;
	
    printf("PWM_update_pwm %d \n",pwm);

    // Determine if PWM is disabled in the registers.??

    // Determine direction of servo movement or stop.
    if (pwm < 0)
    {
        // Less than zero. Turn clockwise.

        // Get the PWM width from the PWM value.
        pwm_width = (uint8_t) -pwm;
        
        // Turn clockwise.
        //See SWAP_PWM_DIRECTION_ENABLED ??
        pwm_dir_a(pwm_width);
    }
    else if (pwm >0)
    {
        // More than zero. Turn counter-clockwise.

        // Get the PWM width from the PWM value.
    	pwm_width = (uint8_t) pwm;

    	// Turn counter-clockwise.
    	//See SWAP_PWM_DIRECTION_ENABLED ??
    	pwm_dir_b(pwm_width);
    }
    else
    {
    	// Stop all PWM activity to the motor.
        PWM_stop();
    }
}
/**
*
*   Stop all PWM signals to the motor.
*
*   @return	    None.
*
*    @note		None.
*
*/
void PWM_stop(void)
{
	if (pwm_a || pwm_b)
	{

	    // Disable PWM0 (GPIO12) and PWM1 (GPIO13)  output.
        pwmWrite(CONFIG_PWM0_GPIO,0);
        pwmWrite(CONFIG_PWM1_GPIO,0);
		
        // Hold EN_A and EN_B low.
        digitalWrite(CONFIG_EN_A_GPIO, 0);
        digitalWrite(CONFIG_EN_B_GPIO, 0);

		// Reset the A and B direction flags.
        pwm_a = 0;
        pwm_b = 0;
	}
	
	// Save the pwm A and B duty values. ???
}


