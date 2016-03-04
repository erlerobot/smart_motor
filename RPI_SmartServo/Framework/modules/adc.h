/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file adc.h
 *  @brief 
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
 *  1.00 jlamperez  1/3/2016  First release
 * 
 *  \endcode
 *
 *	Copyright (c) 2016, Jorge Lampérez. All rights reserved.
 */

#ifndef ADC_H_
#define ADC_H_ 1

#include <signal.h>

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
void ADC_readVoltage();
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