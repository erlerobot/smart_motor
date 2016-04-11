/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file adc.h
 *  @brief Header for the adc module.
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

#ifndef ADC_H_
#define ADC_H_ 1

#include <signal.h>
#include <stdint.h>

extern volatile uint8_t adc_position_ready;
extern volatile uint16_t adc_position_value;

/**
* 	Inline function to get adc_position_value
*/
inline static uint16_t adc_get_position_value()
{
	adc_position_ready = 0;  

	return adc_position_value;
}
/**
* 	Inline function to see if the adc_position_value is ready.
*/
inline static uint8_t adc_position_value_is_ready()
{
	return adc_position_ready;
}
/**
* 	Initialize ADC conversion.
*/
void ADC_init();
/**
* 	Read position from ADC
*/
void ADC_readPosition();
/**
* 	Read voltage from ADC
*/
void ADC_readTemp();
/**
* 	Read current from ADC
*/
void ADC_readCurrent();
/**
* 	Read battery from ADC
*/
void ADC_readBattery();
/**
* 	ADC_handler
*/
void ADC_handler(int sig, siginfo_t *si, void *uc);


#endif
