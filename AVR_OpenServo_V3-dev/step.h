/*
    Copyright (c) 2006 Michael P. Thompson <mpthompson@gmail.com>
        Portions of this code 
    Copyright (c) 2007 Barry Carter <barry.carter@gmail.com>
    Copyright (c) 2008 Jay Ragsdale <j.ragsdale@pendragonobotics.com>	


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

/*This is my attempt at porting the OpenServo_v3_dev branch to the tiny84 for use with the OpenStepper module.*/

#ifndef _OS_STEP_H_
#define _OS_STEP_H_ 1

#if STEP_ENABLED
#include <avr/io.h>
#include "registers.h"
#include "config.h"

void step_registers_defaults(void);
void step_init(void);
void step_update(uint16_t position, int16_t pwm);
void step_stop(void);

inline static void step_enable(void)
{
    uint8_t flags_lo = registers_read_byte(REG_FLAGS_LO);

    // Enable step sequencing to the stepper motor.
    registers_write_byte(REG_FLAGS_LO, flags_lo | (1<<FLAGS_LO_PWM_ENABLED));
}


inline static void step_disable(void)
{
    uint8_t flags_lo = registers_read_byte(REG_FLAGS_LO);

    // Disable step sequencing to the stepper motor.
    registers_write_byte(REG_FLAGS_LO, flags_lo & ~(1<<FLAGS_LO_PWM_ENABLED));

    // Stop now!
    step_stop();
}
#endif  // keep these available as they are used in pwm-std.c

#if STEP_ENABLED || STEP_ENABLE_BRIDGE_PIN
inline static void step_enable_bridge(void)
{
    STEP_ENABLE_PORT |= (1<<STEP_ENABLE_PIN);
}

inline static void step_disable_bridge(void)
{
    STEP_ENABLE_PORT &= ~(1<<STEP_ENABLE_PIN);
}
#endif
#endif // _OS_STEP_H_
