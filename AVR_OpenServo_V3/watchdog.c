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

// Minimal module to support watchdog timer.  This module may be expanded in
// the future to support more robust use of the watchdog timer to monitor
// error conditions in the servo.

#include <inttypes.h>
#include <avr/io.h>

#include "openservo.h"
#include "config.h"
#include "pwm.h"

void watchdog_init(void)
// Initialize the watchdog module.
{
    // Clear WDRF in MCUSR.
    MCUSR &= ~(1<<WDRF);

    // Write logical one to WDCE and WDE.
    WDTCSR |= (1<<WDCE) | (1<<WDE);

    // Turn off WDT.
    WDTCSR = 0x00;
}


void watchdog_hard_reset(void)
// Reset the device using the watchdog timer.
{
    // Disable PWM to the servo motor.
    pwm_disable();

    // Enable the watchdog.
    WDTCSR = (1<<WDIF) |                                     // Reset any interrupt.
             (0<<WDIE) |                                     // Disable interrupt.
             (1<<WDE) |                                      // Watchdog enable.
             (0<<WDP3) | (0<<WDP2) | (0<<WDP1) | (0<<WDP0);  // Minimum prescaling - 16mS.

    // Wait for reset to occur.
    for (;;);
}

