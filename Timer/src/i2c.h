/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file i2c.h
 *  @brief Header I2C module for communication.
 * 
 *  @note 
 *
 *  	Used for ADS1115 communication but can be reusable.
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

#ifndef I2C_H_
#define I2C_H_ 1

#include <stdint.h>

/**
* Read an 8 bit value from a regsiter on the device
*/
uint8_t I2C_readReg8 (int fd, uint8_t reg);
/**
* Read an 16-bit value from a regsiter on the device
*/
uint16_t I2C_readReg16 (int fd, uint8_t reg);
/**
* Write an 8 bit value to the given register
*/
int I2C_writeReg8 (int fd, uint8_t reg, uint16_t value);
/**
* Write an 16-bit value to the given register
*/
int I2C_writeReg16 (int fd, uint8_t reg, uint16_t value);
/**
* Open the I2C device, and register the target device
*/
int I2C_setup (const uint8_t devId);

 #endif