/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file ads1115.c
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

#include "ads1115.h"
#include <stdint.h>
#include "i2c.h"

//Address
static uint8_t ADS1115_address;
//Gain
static uint16_t ADS1115_gain;

static int ADS1115_i2c_fd;

void ADS1115_writeRegister(int fd, uint8_t reg, uint16_t value);
uint16_t ADS1115_readRegister(int fd, uint8_t reg);

void ADS1115_writeRegister(int fd, uint8_t reg, uint16_t value)
{
  I2C_writeReg16 (fd, reg, value);
}

uint16_t ADS1115_readRegister(int fd, uint8_t reg)
{
  return I2C_readReg16 (fd, reg);
}
/**
	Initialization of the ads1115 adc module.
*/
void ADS1115_init(uint8_t address)
{
	ADS1115_address = address;
	//Conversion delay???
	//bitShift???
	ADS1115_gain = ADS1115_REG_CONFIG_PGA_6_144V; /* +/- 6.144V range (limited to VDD +0.3V max!) */

  ADS1115_i2c_fd = I2C_setup(address);
  
}
/**
	Set the ads1115 gain
*/
void ADS1115_setGain(uint16_t gain)
{
	ADS1115_gain = gain;
}
/**
	Get the ads1115 gain
*/
uint16_t ADS1115_getGain()
{
	return ADS1115_gain;
}
/**
	Read the ADC value in singleEnded mode. 4 channels are posible in this mode.
*/
uint16_t ADS1115_readADC_singleEnded(uint8_t channel)
{
	if (channel > 3)
  	{
    	return 0;
  	}

  	/** @todo PONER MI CONFIGURACION*/
  	uint16_t config = ADS1115_REG_CONFIG_CQUE_NONE    | // Disable the comparator (default val)
                    ADS1115_REG_CONFIG_CLAT_NONLAT  | // Non-latching (default val)
                    ADS1115_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
                    ADS1115_REG_CONFIG_CMODE_TRAD   | // Traditional comparator (default val)
                    ADS1115_REG_CONFIG_DR_128SPS   | // 128 samples per second (default)
                    ADS1115_REG_CONFIG_MODE_SINGLE;   // Single-shot mode (default)

  	// Set PGA/voltage range
  	config |= ADS1115_gain;

  	// Set single-ended input channel
  	switch (channel)
  	{
    	case (0):
      		config |= ADS1115_REG_CONFIG_MUX_SINGLE_0;
      		break;
    	case (1):
      		config |= ADS1115_REG_CONFIG_MUX_SINGLE_1;
      		break;
    	case (2):
      		config |= ADS1115_REG_CONFIG_MUX_SINGLE_2;
      		break;
    	case (3):
      		config |= ADS1115_REG_CONFIG_MUX_SINGLE_3;
      		break;
  	}

  	// Set 'start single-conversion' bit
  	config |= ADS1115_REG_CONFIG_OS_SINGLE;

  	// Write config register to the ADC
    ADS1115_writeRegister(ADS1115_i2c_fd, ADS1115_REG_POINTER_CONFIG, config);
  	// Wait for the conversion to complete
    // delay(m_conversionDelay);
  	// Read the conversion results
    return ADS1115_readRegister(ADS1115_i2c_fd, ADS1115_REG_POINTER_CONVERT); 
  	// Shift 12-bit results right 4 bits for the ADS1015
    // return readRegister(m_i2cAddress, ADS1015_REG_POINTER_CONVERT) >> m_bitShift; 
  	// Desplaza para ruido.

}



