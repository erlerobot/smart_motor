/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file i2c.c
 *  @brief I2C module for communication implementation.
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

#include "i2c.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

// I2C definitions

#define I2C_SLAVE	0x0703
#define I2C_SMBUS	0x0720	/* SMBus-level access */

#define I2C_SMBUS_READ	1
#define I2C_SMBUS_WRITE	0

// SMBus transaction types

#define I2C_SMBUS_QUICK		    0
#define I2C_SMBUS_BYTE		    1
#define I2C_SMBUS_BYTE_DATA	    2 
#define I2C_SMBUS_WORD_DATA	    3
#define I2C_SMBUS_PROC_CALL	    4
#define I2C_SMBUS_BLOCK_DATA	    5
#define I2C_SMBUS_I2C_BLOCK_BROKEN  6
#define I2C_SMBUS_BLOCK_PROC_CALL   7		/* SMBus 2.0 */
#define I2C_SMBUS_I2C_BLOCK_DATA    8

// SMBus messages

#define I2C_SMBUS_BLOCK_MAX	32	/* As specified in SMBus standard */	
#define I2C_SMBUS_I2C_BLOCK_MAX	32	/* Not specified but we use same structure */

// Structures used in the ioctl() calls
/**
  Different type of data in the same memory space i2c_smbus_data
*/
union i2c_smbus_data
{
  uint8_t  byte ;
  uint16_t word ;
  uint8_t  block [I2C_SMBUS_BLOCK_MAX + 2] ;	// block [0] is used for length + one more for PEC
} ;
/**
  Struct for i2c_smbus_ioctl_data
*/
struct i2c_smbus_ioctl_data
{
  char read_write ;
  uint8_t command ;
  int size ;
  union i2c_smbus_data *data ;
} ;

static inline int i2c_smbus_access (int fd, char rw, uint8_t command, int size, union i2c_smbus_data *data)
{
  struct i2c_smbus_ioctl_data args ;

  args.read_write = rw ;
  args.command    = command ;
  args.size       = size ;
  args.data       = data ;
  return ioctl (fd, I2C_SMBUS, &args) ;
} 

// Local functions
int I2C_setupInterface (const char *device, int devId);

/**
*
*   Read an 8 bit value from a regsiter on the device
*
*   @param    fd linux file where to read
*   @param    reg the register to read (8 bit)
*
*   @return	  an 8 bit value.
*
*   @note		  None.
*
*/
uint8_t I2C_readReg8 (int fd, uint8_t reg)
{
  union i2c_smbus_data data;

  if (i2c_smbus_access (fd, I2C_SMBUS_READ, reg, I2C_SMBUS_BYTE_DATA, &data))
    return -1 ;
  else
    return data.byte & 0xFF ;
}
/**
*
*   Read an 16-bit value from a regsiter on the device
*
*   @param    fd linux file where to read
*   @param    reg the register to read (8 bit)
*
*   @return	  a 16 bit value.
*
*   @note		  None.
*
*/
uint16_t I2C_readReg16 (int fd, uint8_t reg)
{
  union i2c_smbus_data data;

  if (i2c_smbus_access (fd, I2C_SMBUS_READ, reg, I2C_SMBUS_WORD_DATA, &data))
    return -1 ;
  else
    return data.word & 0xFFFF ;
}
/**
*
*   Write an 8 bit value to the given register
*
*   @param    fd linux file where to read.
*   @param    reg the register to write (8 bit).
*   @param    value the value to write to the register (16 bit).
*
*   @return	  int value.
*
*   @note		  None.
*
*/
int I2C_writeReg8 (int fd, uint8_t reg, uint16_t value)
{
  union i2c_smbus_data data ;

  data.byte = value ;
  return i2c_smbus_access (fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &data) ;
}
/**
*
*   Write an 16-bit value to the given register
*
*   @param    fd linux file where to read.
*   @param    reg the register to write (8 bit).
*   @param    value the value to write to the register (16 bit).
*
*   @return   int value.
*
*   @note     None.
*
*/
int I2C_writeReg16 (int fd, uint8_t reg, uint16_t value)
{
  union i2c_smbus_data data ;

  data.word = value ;
  return i2c_smbus_access (fd, I2C_SMBUS_WRITE, reg, I2C_SMBUS_WORD_DATA, &data) ;
}
/**
*
*   Interface for I2C
*
*   @param    device /dev/i2c-1. 
*   @param    devId .
*
*   @return	  None.
*
*   @note		  /dev/i2c-1.
*
*/
int I2C_setupInterface (const char *device, int devId)
{
  int fd ;

  if ((fd = open (device, O_RDWR)) < 0)
  {
  	printf("Unable to open the i2c port!\n");
	exit(1);
  }
   
  if (ioctl (fd, I2C_SLAVE, devId) < 0)
  {
	close(fd);
	perror("Unable to setup the i2c port!\n");
	exit(1);
  }
    
  return fd ;
}
/**
*
*   Open the I2C device, and register the target device
*
*   @param  	devId
*
*   @return	  None.
*
*   @note		 /dev/i2c-1.
*
*/
int I2C_setup (const uint8_t devId)
{
  const char *device ;

  /**
	@todo only version2
  */
  device = "/dev/i2c-1" ;

  return I2C_setupInterface (device,devId);
}


 