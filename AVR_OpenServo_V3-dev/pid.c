/*
    Copyright (c) 2006 Michael P. Thompson <mpthompson@gmail.com>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    $Id$
*/

#include <inttypes.h>

#include "openservo.h"
#include "config.h"
#include "pid.h"
#include "registers.h"
#include "banks.h"
#include "filter.h"

// The minimum and maximum servo position as defined by 10-bit ADC values.
#define MIN_POSITION            (0)
#define MAX_POSITION            (1023)

// The minimum and maximum output.
#define MAX_OUTPUT              (255)
#define MIN_OUTPUT              (-MAX_OUTPUT)

// Values preserved across multiple PID iterations.
static int16_t previous_seek;
static int16_t previous_position;

static int32_t filter_reg_pos = 0;
#if BACKEMF_ENABLED
static int32_t filter_reg_emf = 0;
#endif

void pid_init(void)
// Initialize the PID algorithm module.
{
    // Initialize preserved values.
    previous_seek = 0;
    previous_position = 0;
}


void pid_registers_defaults(void)
// Initialize the PID algorithm related register values.  This is done
// here to keep the PID related code in a single file.
{
    // Default deadband.
    banks_write_byte(POS_PID_BANK, REG_PID_DEADBAND, DEFAULT_PID_DEADBAND);

    // Default gain values.
    banks_write_word(POS_PID_BANK, REG_PID_PGAIN_HI, REG_PID_PGAIN_LO, DEFAULT_PID_PGAIN);
    banks_write_word(POS_PID_BANK, REG_PID_DGAIN_HI, REG_PID_DGAIN_LO, DEFAULT_PID_DGAIN);
    banks_write_word(POS_PID_BANK, REG_PID_IGAIN_HI, REG_PID_IGAIN_LO, DEFAULT_PID_IGAIN);

    // Default position limits.
    banks_write_word(POS_PID_BANK, REG_MIN_SEEK_HI, REG_MIN_SEEK_LO, DEFAULT_MIN_SEEK);
    banks_write_word(POS_PID_BANK, REG_MAX_SEEK_HI, REG_MAX_SEEK_LO, DEFAULT_MAX_SEEK);

    // Default reverse seek setting.
    banks_write_byte(POS_PID_BANK, REG_REVERSE_SEEK, 0x00);
}


int16_t pid_position_to_pwm(int16_t current_position)
// This is a modified pid algorithm by which the seek position and seek
// velocity are assumed to be a moving target.  The algorithm attempts to
// output a pwm value that will achieve a predicted position and velocity.
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
    static int16_t filtered_position;
    static int32_t pwm_output;
    static uint16_t d_gain;
    static uint16_t p_gain;

    // Filter the current position thru a digital low-pass filter.
    filtered_position = filter_update(current_position, &filter_reg_pos);

#if BACKEMF_ENABLED
    int16_t sign;
    // Use the filtered position to determine velocity.
    sign = filtered_position - previous_position;
    if (sign < 0)
        sign = -1;
    else
        sign = 1;

    current_velocity  = sign * filter_update(banks_read_word(INFORMATION_BANK, REG_BACKEMF_HI, REG_BACKEMF_LO), &filter_reg_emf);

    previous_position = filtered_position;

#else
    // Use the filtered position to determine velocity.
    current_velocity = filtered_position - previous_position;
    previous_position = filtered_position;
#endif

    // Get the seek position and velocity.
    seek_position = (int16_t) registers_read_word(REG_SEEK_POSITION_HI, REG_SEEK_POSITION_LO);
    seek_velocity = (int16_t) registers_read_word(REG_SEEK_VELOCITY_HI, REG_SEEK_VELOCITY_LO);

    // Get the minimum and maximum position.
    minimum_position = (int16_t) banks_read_word(POS_PID_BANK, REG_MIN_SEEK_HI, REG_MIN_SEEK_LO);
    maximum_position = (int16_t) banks_read_word(POS_PID_BANK, REG_MAX_SEEK_HI, REG_MAX_SEEK_LO);

    // Are we reversing the seek sense?
    if (banks_read_byte(POS_PID_BANK, REG_REVERSE_SEEK) != 0)
    {
        // Yes. Update the position and velocity using reverse sense.
        registers_write_word(REG_POSITION_HI, REG_POSITION_LO, (uint16_t) (MAX_POSITION - current_position));
        registers_write_word(REG_VELOCITY_HI, REG_VELOCITY_LO, (uint16_t) -current_velocity);

        // Reverse sense the seek and other position values.
        seek_position = MAX_POSITION - seek_position;
        minimum_position = MAX_POSITION - minimum_position;
        maximum_position = MAX_POSITION - maximum_position;
    }
    else
    {
        // No. Update the position and velocity registers without change.
        registers_write_word(REG_POSITION_HI, REG_POSITION_LO, (uint16_t) current_position);
        registers_write_word(REG_VELOCITY_HI, REG_VELOCITY_LO, (uint16_t) current_velocity);
    }

    // Get the deadband.
    deadband = (int16_t) banks_read_byte(POS_PID_BANK, REG_PID_DEADBAND);

    // Use the filtered position when the seek position is not changing.
    if (seek_position == previous_seek) current_position = filtered_position;
    previous_seek = seek_position;

    // Keep the seek position bound within the minimum and maximum position.
    if (seek_position < minimum_position) seek_position = minimum_position;
    if (seek_position > maximum_position) seek_position = maximum_position;

    // The proportional component to the PID is the position error.
    p_component = seek_position - current_position;

    // Get the proportional, derivative and integral gains.
    p_gain = banks_read_word(POS_PID_BANK, REG_PID_PGAIN_HI, REG_PID_PGAIN_LO);
    d_gain = banks_read_word(POS_PID_BANK, REG_PID_DGAIN_HI, REG_PID_DGAIN_LO);

    // Start with zero PWM output.
    pwm_output = 0;

    // Apply proportional component to the PWM output if outside the deadband.
    if ((p_component > deadband) || (p_component < -deadband))
    {
        // Apply the proportional component of the PWM output.
        pwm_output += (int32_t) p_component * (int32_t) p_gain;

        // Reset the speed portion of the motion to zero when in deadband. Stops D error increasing.
        seek_velocity = 0;
    }

    // The derivative component to the PID is the velocity.
    d_component = seek_velocity - current_velocity;

    // Apply the derivative component of the PWM output.
    pwm_output += (int32_t) d_component * (int32_t) d_gain;

    // Shift by 8 to account for the multiply by the 8:8 fixed point gain values.
    pwm_output >>= 8;

    // Check for output saturation.
    if (pwm_output > MAX_OUTPUT)
    {
        // Can't go higher than the maximum output value.
        pwm_output = MAX_OUTPUT;
    }
    else if (pwm_output < MIN_OUTPUT)
    {
        // Can't go lower than the minimum output value.
        pwm_output = MIN_OUTPUT;
    }

    // Return the PID output.
    return (int16_t) pwm_output;
}

