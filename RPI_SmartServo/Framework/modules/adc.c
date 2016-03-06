/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file adc.c
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

#include "adc.h"
#include <stdio.h>
#include "ads1115.h"
#include "registers.h"
#include <signal.h>


volatile uint8_t adc_position_ready;
volatile uint16_t adc_position_value;


/**
*
* Initialize ADC conversion.
*
* @return	None.
*
* @note		None.
*
*/
void ADC_init(void)
{	
	printf("ADC initialization\n");
	ADS1115_init(ADS1115_ADDRESS);
	adc_position_ready = 0;
	adc_position_value = 0;
}
/**
*
* Read position from ADC
*
* @return	None.
*
* @note		None.
*
*/
void ADC_readPosition()
{
	printf("ADC_readPosition\n"); 
	
	// Read from i2C
	adc_position_value = ADS1115_readADC_singleEnded(POSITION_CHANNEL);
	printf("ADC position value is: %d \n", adc_position_value);			
	// Save value in registers position.
	set_position (adc_position_value);
	// Put flag to 1.
	adc_position_ready =1;
}
/**
*
* Read voltage from ADC
*
* @return	None.
*
* @note		None.
*
*/
void ADC_readVoltage()
{
	/** @todo */
}
/**
*
* Read current from ADC
*
* @return	None.
*
* @note		None.
*
*/
void ADC_readCurrent()
{
	/** @todo */
}
/**
*
* Read battery from ADC
*
* @return	None.
*
* @note		None.
*
*/
void ADC_readBattery()
{
	/** @todo */


}

/**
*
* ADC handler for the timer signal. 
*
* @param sig ...
*
* @return	None.
*
* @note		None.
*
*/
void ADC_handler(int sig, siginfo_t *si, void *uc)
{
	// Handle ADC interrupt

	// Read 16 bit ADC value

		// POSITION (Potenciometer)
		ADC_readPosition();
			// Save the new position value.
			// Flag the position value ready.
			// Start the ADC of the power(current) channel

		// CURRENT
		ADC_readCurrent();
			// Save the new power value
			// Flag the power value as ready
			// Is adc_voltage needed??

		// BATTERY
		ADC_readBattery();
			// Save voltage value.

		ADC_readVoltage();
}




