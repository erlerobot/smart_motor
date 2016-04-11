/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file adc.c
 *  @brief Adc module implementation. It works like an interface for different adc's, now ads1115 adc is used.
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


#include <signal.h>
#include <stdio.h>
#include "adc.h"
#include "ads1115.h"
#include "registers.h"
#include "../../config.h"



volatile uint8_t adc_position_ready;
volatile uint16_t adc_position_value;


/**
*
* Initialize ADC conversion.
*
* @return	None.
*
* @note		ADC used, ADS1115. 
*
*/
void ADC_init()
{	
#ifdef CONFIG_DEBUGGER
	printf("ADC initialization\n");
#endif
	// Init ADS1115 adc.
	ADS1115_init(ADS1115_ADDRESS);
	// Init module global variables.
	adc_position_ready = 0;
	adc_position_value = 0;
}
/**
*
* Read position from ADC. 
*
* @return	None.
*
* @note		None.
*
*/
void ADC_readPosition()
{
#ifdef CONFIG_DEBUGGER
	printf("ADC_readPosition\n"); 
#endif
	// Read from i2C
	adc_position_value = ADS1115_readADC_singleEnded(POSITION_CHANNEL);
#ifdef CONFIG_DEBUGGER
	printf("ADC position value is: %d \n", adc_position_value);			
#endif
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
	uint16_t adc_voltage_value;
	adc_temp_value = ADS1115_readADC_singleEnded(VOLTAGE_CHANNEL);
	set_voltage(adc_temp_value);

        //float temp = (single_read*0.1875)/1000; //for 15 bits
        float temp = (adc_temp_value*1.5)/1000; //for 12 bits
        printf("ADS1115 Voltage is: %f \n", voltage);

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
	uint16_t adc_current_value;
	adc_current_value = ADS1115_readADC_singleEnded(CURRENT_CHANNEL);
	set_current(adc_current_value);
        
        //float voltage = (single_read*1.5)/1000; //for 12 bits
        //printf("ADS1115 Voltage is: %f \n", voltage);

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
	uint16_t adc_battery_value;
	adc_battery_value = ADS1115_readADC_singleEnded(BATTERY_CHANNEL);
	set_battery(adc_battery_value);

        float voltage = (single_read*1.5)/1000; //for 12 bits
        printf("ADS1115 Voltage is: %f \n", voltage);

}
/**
*
* ADC handler for the timer signal. Read 16 bit ADC value.
*
* @param 	sig 
* @param 	si 
* @param 	uc 
*
* @return	None.
*
* @note		None.
*
*/
void ADC_handler(int sig, siginfo_t *si, void *uc)
{

	// POSITION (Potenciometer)
	ADC_readPosition();
	// CURRENT
	ADC_readCurrent();
	// BATTERY
	ADC_readBattery();
	//VOLTAGE
	ADC_readVoltage();
}




