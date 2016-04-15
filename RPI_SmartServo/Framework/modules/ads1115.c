/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file ads1115.c
 *  @brief Implementation of the ads1115 adc converter module.
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

#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>
#include "ads1115.h"
#include "i2c.h"
#include "../../config.h"

//Address
static uint8_t ADS1115_address;
//Gain
static uint16_t ADS1115_gain;
//Bit shift
static uint8_t ADS1115_bitShift;
//Conversion delay
static uint8_t ADS1115_delay;
//ADS1115 i2c file
static int ADS1115_i2c_fd;

/**
*   Local functions
*/
void ADS1115_writeRegister(int fd, uint8_t reg, uint16_t value);
uint16_t ADS1115_readRegister(int fd, uint8_t reg);

/**
*   Function to write in an ADS1115 register.
*
*   @param    fd linux file for ADS1115.
*   @param    reg the register to write.
*   @param    value the value to write in the register.
*
*   @return   None.
*
*   @note     None. 
*/
void ADS1115_writeRegister(int fd, uint8_t reg, uint16_t value)
{
#ifdef CONFIG_DEBUGGER
	printf("ADS1115_writeRegister\n");
#endif

  uint8_t highWriteValue8 = value & 0xFF;
  uint8_t lowWriteValue8 = (value>>8)&0xFF;		
  I2C_writeReg16 (fd, reg, highWriteValue8<<8 |lowWriteValue8);

}
/**
*   Function to read from an ADS1115 register.
*
*   @param    fd linux file for ADS1115.
*   @param    reg the register to read.
*
*   @return   None.
*
*   @note     The I2C read value is swap to have a correct value. 
*/
uint16_t ADS1115_readRegister(int fd, uint8_t reg)
{
#ifdef CONFIG_DEBUGGER
  printf("ADS1115_readRegister\n");
#endif

  //swap read high and low registers. 
  uint16_t readRegValue16 = I2C_readReg16(fd, reg);
  uint8_t highRegValue8 = readRegValue16 & 0xFF;
  uint8_t lowRegValue8 = (readRegValue16>>8)&0xFF;	
   
  uint16_t readValue16 = highRegValue8<<8 |lowRegValue8;

  if(reg == ADS1115_REG_POINTER_CONVERT)
  {
	  readValue16 = readValue16 >> ADS1115_bitShift;  //12 bit efective resolution ADC (noise)
  }

  return readValue16;
}
/**
*   Initialization for the ADS1115 adc.
*
*   @param    address the i2c addreess for communication with ADS1115.
*
*   @return   None.
*
*   @note     None. 
*   @todo     See if a bitShift is need for noise and a conversion delay.
*/
void ADS1115_init(uint8_t address)
{
	ADS1115_address = address;
	ADS1115_delay = 2;
	ADS1115_bitShift = 3;
	ADS1115_gain = ADS1115_REG_CONFIG_PGA_6_144V; /* 4_096 +/- 6.144V range (limited to VDD +0.3V max!) */

    ADS1115_i2c_fd = I2C_setup(address);
}
/**
*   Set the ads1115 gain.
*
*   @param    gain the value for the gain field.
*
*   @return   None.
*
*   @note     None. 
*/
void ADS1115_setGain(uint16_t gain)
{
	ADS1115_gain = gain;
}
/**
*   Get the ads1115 gain.
*
*   @return     Gain value.
*
*   @note       None. 
*/
uint16_t ADS1115_getGain()
{
	return ADS1115_gain;
}
/**
*   Read the ADC value in singleEnded mode. 4 channels are posible in this mode.
*
*   @param      channel Which channel from the ADS1115 is going to be measured.
*
*   @return     Single read of 16 bits value.
*
*   @note       None. 
*/
uint16_t ADS1115_readADC_singleEnded(uint8_t channel)
{	
#ifdef CONFIG_DEBUGGER
	printf("ADC_ADS1115_readADC_singleEnded\n");
#endif

	if (channel > 3)
  	{
    	return 0;
  	}

  // Configuration of the ADS1115
  uint16_t config = ADS1115_REG_CONFIG_CQUE_NONE    | // Disable the comparator 
                    ADS1115_REG_CONFIG_CLAT_NONLAT  | // Non-latching 
                    ADS1115_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   
                    ADS1115_REG_CONFIG_CMODE_TRAD   | // Traditional comparator 
                    ADS1115_REG_CONFIG_DR_860SPS    | // 128 samples per second 
                    ADS1115_REG_CONFIG_MODE_SINGLE;   // Single-shot mode 

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
  delay(ADS1115_delay); //@todo see delay.


#ifdef CONFIG_DEBUGGER
  //read config register
  uint16_t config_read = ADS1115_readRegister(ADS1115_i2c_fd, ADS1115_REG_POINTER_CONFIG) ;
	// Read the conversion results
  uint16_t single_read = ADS1115_readRegister(ADS1115_i2c_fd, ADS1115_REG_POINTER_CONVERT) ;
    	
  printf("ADS1115 config value is: %d, %.4x \n", config_read, config_read);
  printf("ADS1115 single_read value is: %d, %.4x \n", single_read, single_read);
  
#endif
    	
  return single_read;

}



