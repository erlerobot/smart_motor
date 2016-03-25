/**
 *  project  :  RPI_SmartServo          
 *  
 *  @file config.h
 *  @brief Configuration file for RPI_SmartServo
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

#ifndef CONFIG_H_
#define CONFIG_H_ 1

/** Define different options for SmartServo.
	@todo todo
	Configuration for the ADS1115
*/

/**
 *  Board.  
 *  @todo PWM and EN GPIO can be changed
 */

#define RPI_0 0     //For raspberry pi 0
#define RPI_1 1     //For raspberry pi one
#define RPI_2 2     //For raspberry pi two

/**
 *  Debugger configuration.
 */

//#define CONFIG_DEBUGGER 0

/**
 *  TIMER configuration.
 */

#define CONFIG_TIMER 100000000

/**
 *  PID configuration.
 */

// The minimum and maximum servo position as defined by 12-bit ADC values.
#define CONFIG_PID_MIN_POSITION (0)
#define CONFIG_PID_MAX_POSITION (4096) //The ADC effective bits are 15 but because of noise we take 12.
// The minimum and maximum output.
#define CONFIG_PID_MAX_OUTPUT          (255)
#define CONFIG_PID_MIN_OUTPUT          (-CONFIG_PID_MAX_OUTPUT)
// Default PID values
#define CONFIG_DEFAULT_PID_DEADBAND    0x01
#define CONFIG_DEFAULT_PID_PGAIN       0x0060
#define CONFIG_DEFAULT_PID_DGAIN       0x0000
#define CONFIG_DEFAULT_PID_IGAIN       0x0000
// Max and min seek values
#define CONFIG_DEFAULT_MIN_SEEK        0x0001
#define CONFIG_DEFAULT_MAX_SEEK        0x0CFD //0x0D08

/**
 *  PWM and EN configuration.
 */

// PWM frequency = 19.2 Mhz/PWM_RANGE/CLOCK_DIV.
// PWM frequency of 9765.525 Hz with next two config values.
//#define CONFIG_PWM_RANGE 1024
#define CONFIG_PWM_RANGE 4096  //f=2343.75Hz
#define CONFIG_PWM_CLOCK_DIV 2
// Delay between direction change of the chopper
// This value should be maximum the period of the PWM
//#define	CONFIG_PWM_DIR_CHANGE_DELAY	100 //for 1024
#define	CONFIG_PWM_DIR_CHANGE_DELAY	500  //for 4096
// PWM maximum position value
//#define CONFIG_PWM_MAX_POSITION  (1023)
#define CONFIG_PWM_MAX_POSITION  (4095)
// PWM GPIO
#define CONFIG_PWM0_GPIO 12 // pin 32
#define CONFIG_PWM1_GPIO 13 // pin 33
// EN_A and EN_N GPIO
#define CONFIG_EN_A_GPIO 16 //pin36
#define CONFIG_EN_B_GPIO 19 //pin35

/**********************************************/

#endif //CONFIG_H_

