/**
 *  project  :  RPI_SmartServo          
 *  
 *  @file pid.c
 *  @brief PID module implementation.
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
#include "../../config.h"
#include "pid.h"
#include "registers.h"

// Values preserved across multiple PID iterations.
static int16_t previous_seek;
static int16_t previous_position;

/**
*
*   Initialize the pid algorithm module.
*
*   @return	  None.
*
*   @note	      None.
*
*/
void PID_init(void)
{

    // Initialize preserved values.
    previous_seek = 0;
    previous_position = 0;
    PID_registers_default();

}

/**
*
*   Initialize the pid related registers.
*
*   @return	  None.
*
*   @note	  None.
*
*/
void PID_registers_default(void)
{
	//Default deadband
    set_pid_deadband((uint8_t) CONFIG_DEFAULT_PID_DEADBAND);
	// Default gain values
    set_pid_pgain ((uint16_t) CONFIG_DEFAULT_PID_PGAIN);
    set_pid_dgain ((uint16_t) CONFIG_DEFAULT_PID_DGAIN);
    set_pid_igain ((uint16_t) CONFIG_DEFAULT_PID_IGAIN);
	// Default position limits
    set_min_seek ((uint16_t) CONFIG_DEFAULT_MIN_SEEK);
    set_max_seek ((uint16_t) CONFIG_DEFAULT_MAX_SEEK);
	// Default reverse seeking

}

/**
*
*   This is a modified pid algorithm by which the seek position and seek 
*   velocity are assumed to be a moving target.  The algorithm attempts to 
*   output a pwm value that will achieve a predicted position and 
*   velocity. 
*   Take position as input and output assigned PWM to be applied to the 
*   servo motors.
*
*   @param    current_position current position of the potentiometer.
*
*   @return   pwm value (-255 to 255).
*
*   @note     position (0-1024)
*
*/
int16_t PID_position_to_pwm(int16_t current_position)
{
    // We declare these static to keep them off the stack.
    static int16_t deadband;
    static int16_t p_component;
    static int16_t d_component;
    static int16_t seek_position;
    static int16_t seek_velocity;
    static int16_t minimum_position;
    static int16_t maximum_position;
    static int16_t current_velocity;
//  static int16_t filtered_position;
    static int32_t pwm_output;
    static uint16_t d_gain;
    static uint16_t p_gain;

    // Filter the current position thru a digital low-pass filter.
    // Esto se puede quitar tiene un if 0 que lo comenta
    //filtered_position = filter_update(current_position);
    // Use the filtered position to determine velocity.
    //current_velocity = filtered_position - previous_position;
    //previous_position = filtered_position;
    current_velocity = current_position - previous_position;

    previous_position = current_position;

    // Get the seek position and velocity.
    seek_position = get_seek_position();
    seek_velocity = get_seek_velocity();

    // Get the minimum and maximum position.
    minimum_position = get_min_seek();
    maximum_position = get_max_seek();
    	

    /*
    // Are we reversing the seek sense
    // Not this option yet.
    */

    // No. Update the position and velocity registers without change.
    set_position(current_position);
    set_velocity(current_velocity);
    // Get the deadband.
    deadband = get_pid_deadband();
    // Use the filtered position when the seek position is not changing.
    //if (seek_position == previous_seek) current_position = filtered_position;
    previous_seek = seek_position;
    // Keep the seek position bound within the minimum and maximum position.
    if (seek_position < minimum_position) seek_position = minimum_position;
    if (seek_position > maximum_position) seek_position = maximum_position;
    // The proportional component to the PID is the position error.
    p_component = seek_position - current_position;

    // The derivative component to the PID is the velocity.
    d_component = seek_velocity - current_velocity;
 
    // Get the proportional, derivative and integral gains.
    p_gain = get_pid_pgain();
    d_gain = get_pid_dgain();
    // Start with zero PWM output.
    pwm_output = 0;

    // Apply proportional component to the PWM output if outside the deadband.
    if ((p_component > deadband) || (p_component < -deadband))
    {
        // Apply the proportional component of the PWM output.
        pwm_output += (int32_t) p_component * (int32_t) p_gain;
    }

    // Apply the derivative component of the PWM output.
    pwm_output += (int32_t) d_component * (int32_t) d_gain;

    // Shift by 8 to account for the multiply by the 8:8 fixed point gain values.
    pwm_output >>= 8;

        // Check for output saturation.
    if (pwm_output > CONFIG_PID_MAX_OUTPUT)
    {
        // Can't go higher than the maximum output value.
        pwm_output = CONFIG_PID_MAX_OUTPUT;
    }
    else if (pwm_output < CONFIG_PID_MIN_OUTPUT)
    {
        // Can't go lower than the minimum output value.
        pwm_output = CONFIG_PID_MIN_OUTPUT;
    }

#ifdef CONFIG_DEBUGGER
    printf("PID_minimum_position: %d\n",minimum_position);
    printf("PID_maximum_position: %d\n",maximum_position);
    printf("PID_current_position: %d\n",current_position);
    printf("PID_seek_position: %d\n",seek_position);
    printf("PID_seek_velocity: %d\n",seek_velocity);
    printf("PID_deadband: %d\n",deadband);
    printf("PID_p_component: %d\n",p_component);
    printf("PID_d_component: %d\n",d_component);
    printf("PID_p_gain: %d\n",p_gain);
    printf("PID_d_gain: %d\n",d_gain);
    printf("PID pwm value is: %d \n", pwm_output);
#endif
    // Return the PID output.
    return (int16_t) pwm_output;
}
