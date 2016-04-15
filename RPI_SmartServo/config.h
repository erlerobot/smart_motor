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

#define RPI_0 0
#define RPI_1 1
#define RPI_2 2

#define BITS_12 12
#define BITS_10 10

/** Define different options for RPI Servo.
 @todo todo
 Configuration for the ADS1115
 */
#define RPI_BOARD RPI_2
#define ADC_RESOLUTION BITS_12

/**
 *  TIMER configuration.
 */
#define CONFIG_TIMER 100000000 //100ms
//#define CONFIG_TIMER  10000000 //10ms

/**
 *  Debugger configuration.
 */

//#define CONFIG_DEBUGGER 0

/**
 *  Board.  RPI_0, RPI_1, RPI_2
 *  PWM and EN GPIO can be changed
 */

/*
 * RPIO_0
 */
#if (RPI_BOARD == 0)
// PWM GPIO
#define CONFIG_PWM0_GPIO X // pin X
#define CONFIG_PWM1_GPIO X // pin X
// EN_A and EN_N GPIO
#define CONFIG_EN_A_GPIO X //pin X
#define CONFIG_EN_B_GPIO X //pin X
/*
 * RPIO_1
 */
#elif (RPI_BOARD == 1)
// PWM GPIO
#define CONFIG_PWM0_GPIO 12 // pin X
#define CONFIG_PWM1_GPIO 13 // pin X
// EN_A and EN_N GPIO
#define CONFIG_EN_A_GPIO 16 //pin X
#define CONFIG_EN_B_GPIO 19 //pin X
/*
 * RPIO_2
 */
#elif (RPI_BOARD == 2)
// PWM GPIO
#define CONFIG_PWM0_GPIO 12 // pin 32
#define CONFIG_PWM1_GPIO 13 // pin 33
// EN_A and EN_N GPIO
#define CONFIG_EN_A_GPIO 16 //pin36
#define CONFIG_EN_B_GPIO 19 //pin35
#endif


/**
 *  ADC resolution configuration for pid and pwm
 */

/*
 * ADC 10 bits
 */
#if (ADC_RESOLUTION == BITS_10)
/**
 *  ADC and Potentiometer resolution values to convert to voltage and grades
 */
#define ADC_RES_CONSTANT 0.006  //(6.1444/2^10)
#define POT_RES_CONSTANT 3.78   //(5V/ADC_RES)/220º
/**
 *  PID configuration.
 */

// The minimum and maximum servo position as defined by 10-bit ADC values.
#define CONFIG_PID_MIN_POSITION (0)
//The ADC effective bits are 15 but because of noise we take 10.
#define CONFIG_PID_MAX_POSITION (1024)
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
#define CONFIG_DEFAULT_MAX_SEEK        0x0CFD

/**
 *  PWM and EN configuration.
 */

// PWM frequency = 19.2 Mhz/PWM_RANGE/CLOCK_DIV.
// PWM frequency of 9765.525 Hz with next two config values.
#define CONFIG_PWM_RANGE 1024
#define CONFIG_PWM_CLOCK_DIV 2
// Delay between direction change of the chopper
// This value should be maximum the period of the PWM
#define	CONFIG_PWM_DIR_CHANGE_DELAY	100 //for 1024
// PWM maximum position value
#define CONFIG_PWM_MAX_POSITION  (1023)

/*
 * ADC 12 bits
 */
#elif (ADC_RESOLUTION == BITS_12)
/**
 *  ADC and Potentiometer resolution values to convert to voltage and grades
 */
#define ADC_RES_CONSTANT 0.0015  //(6.144/2^12)
#define POT_RES_CONSTANT 15.15   //(5V/ADC_RES)/220º
/**
 *  PID configuration.
 */
// The minimum and maximum servo position as defined by 12-bit ADC values.
#define CONFIG_PID_MIN_POSITION (0)
//The ADC effective bits are 15 but because of noise we take 12.
#define CONFIG_PID_MAX_POSITION (4096)
// The minimum and maximum output.
#define CONFIG_PID_MAX_OUTPUT          (255)
#define CONFIG_PID_MIN_OUTPUT          (-CONFIG_PID_MAX_OUTPUT)
// Default PID values
#define CONFIG_DEFAULT_PID_DEADBAND    0x01
#define CONFIG_DEFAULT_PID_PGAIN       0x0028
#define CONFIG_DEFAULT_PID_DGAIN       0x0023
#define CONFIG_DEFAULT_PID_IGAIN       0x0000
// Max and min seek values
#define CONFIG_DEFAULT_MIN_SEEK        0x0001
#define CONFIG_DEFAULT_MAX_SEEK        0x0CFD //0x0D08
/**
 *  PWM and EN configuration.
 */
// PWM frequency = 19.2 Mhz/PWM_RANGE/CLOCK_DIV.
// PWM frequency of 2343.75Hz Hz with next two config values.
#define CONFIG_PWM_RANGE 4096
#define CONFIG_PWM_CLOCK_DIV 2
// Delay between direction change of the chopper
// This value should be maximum the period of the PWM
#define	CONFIG_PWM_DIR_CHANGE_DELAY	500  //for 4096
// PWM maximum position value
#define CONFIG_PWM_MAX_POSITION  (4095)
#endif


#endif //CONFIG_H_

