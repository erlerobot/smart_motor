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

#ifndef _OS_CONFIG_H_
#define _OS_CONFIG_H_ 1

// Enable (1) or disable (0) Servomotor characteristics
#define TWI_CHECKED_ENABLED         1
#define CURVE_MOTION_ENABLED        1
#define MAIN_MOTION_TEST_ENABLED    0
#define PULSE_CONTROL_ENABLED       0
#define SWAP_PWM_DIRECTION_ENABLED  0
#define ENCODER_ENABLED             0
#define FULL_ROTATION_ENABLED       0

// The known OpenServo hardware types are listed below.
#define HARDWARE_TYPE_UNKNOWN           0
#define HARDWARE_TYPE_FUTABA_S3003      1
#define HARDWARE_TYPE_HITEC_HS_311      2
#define HARDWARE_TYPE_HITEC_HS_475HB    3
#define HARDWARE_TYPE_MG995             4

// By default the hardware type is unknown.  This value should be
// changed to reflect the hardware type that the code is actually
// being compiled for.
#define HARDWARE_TYPE                   HARDWARE_TYPE_UNKNOWN

// Set configuration values based on HARDWARE_TYPE.
#if (HARDWARE_TYPE == HARDWARE_TYPE_UNKNOWN)

// PID configuration
#define DEFAULT_PID_PGAIN               0x0000
#define DEFAULT_PID_DGAIN               0x0000
#define DEFAULT_PID_IGAIN               0x0000
#define DEFAULT_PID_DEADBAND            0x00

// Specify default mininimum and maximum seek positions.  The OpenServo will
// not attempt to seek beyond these positions.
#define DEFAULT_MIN_SEEK_STD                0x0060
#define DEFAULT_MAX_SEEK_STD                0x03A0

// Default pwm frequency divider.
#define DEFAULT_PWM_FREQ_DIVIDER        0x0040

#elif (HARDWARE_TYPE == HARDWARE_TYPE_FUTABA_S3003)

#error "Values not verified with this firmware"
// Futaba S3003 hardware default PID gains.
#define DEFAULT_PID_PGAIN               0x0600
#define DEFAULT_PID_DGAIN               0x0C00
#define DEFAULT_PID_IGAIN               0x0000
#define DEFAULT_PID_DEADBAND            0x01

// Futaba S3003 hardware default mininimum and maximum seek positions.
#define DEFAULT_MIN_SEEK_STD                0x0060
#define DEFAULT_MAX_SEEK_STD                0x03A0

// Futaba S3003 hardware default pwm frequency divider.
#define DEFAULT_PWM_FREQ_DIVIDER        0x0040

#elif (HARDWARE_TYPE == HARDWARE_TYPE_HITEC_HS_311)

#error "Values not verified with this firmware"
// Hitec HS-311 hardware default PID gains.
#define DEFAULT_PID_PGAIN               0x0600
#define DEFAULT_PID_DGAIN               0x0C00
#define DEFAULT_PID_IGAIN               0x0000
#define DEFAULT_PID_DEADBAND            0x01

// Hitec HS-311 hardware default mininimum and maximum seek positions.
#define DEFAULT_MIN_SEEK_STD                0x0060
#define DEFAULT_MAX_SEEK_STD                0x03A0

// Hitec HS-311 hardware default pwm frequency divider.
#define DEFAULT_PWM_FREQ_DIVIDER        0x0040

#elif (HARDWARE_TYPE == HARDWARE_TYPE_HITEC_HS_475HB)

#error "Values not verified with this firmware"
// Hitec HS-475HB hardware default PID gains.
#define DEFAULT_PID_PGAIN               0x0600
#define DEFAULT_PID_DGAIN               0x0C00
#define DEFAULT_PID_IGAIN               0x0000
#define DEFAULT_PID_DEADBAND            0x01

// Hitec HS-475HB hardware default mininimum and maximum seek positions.
#define DEFAULT_MIN_SEEK_STD                0x0060
#define DEFAULT_MAX_SEEK_STD                0x03A0

// Hitec HS-475HB hardware default pwm frequency divider.
#define DEFAULT_PWM_FREQ_DIVIDER        0x0040

#elif (HARDWARE_TYPE == HARDWARE_TYPE_MG995)

#define DEFAULT_PID_PGAIN               0x01a0 // Working un-tuned example
#define DEFAULT_PID_DGAIN               0x0120 //   "
#define DEFAULT_PID_IGAIN               0x0004 //   "
#define DEFAULT_PID_DEADBAND            0x01
#define DEFAULT_MIN_SEEK_STD            100    // Conservative
#define DEFAULT_MAX_SEEK_STD            900    // Conservative
#define DEFAULT_PWM_FREQ_DIVIDER        0x0040

#endif

//
// Update minimum and maximum seek positions depending on whether the encoder is
// used and/or full rotation is enabled.
//
#if FULL_ROTATION_ENABLED
#if ENCODER_ENABLED
#define DEFAULT_MIN_SEEK                0
#define DEFAULT_MAX_SEEK                4095
#else
#define DEFAULT_MIN_SEEK                0
#define DEFAULT_MAX_SEEK                1023
#endif
#else
#if ENCODER_ENABLED
#define DEFAULT_MIN_SEEK                (DEFAULT_MIN_SEEK_STD<<1)
#define DEFAULT_MAX_SEEK                (DEFAULT_MAX_SEEK_STD<<1)
#else
#define DEFAULT_MIN_SEEK                DEFAULT_MIN_SEEK_STD
#define DEFAULT_MAX_SEEK                DEFAULT_MAX_SEEK_STD
#endif
#endif

#endif // _OS_ADC_H_
