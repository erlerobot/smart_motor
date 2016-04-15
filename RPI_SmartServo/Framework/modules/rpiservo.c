/**
 *  project  : 	RPI_SmartServo
 *
 * 	@file rpiservo.c
 *  @brief Implementation for rpiservo module, interface for communication.
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
 *  1.00 jlamperez  10/4/2016  First release
 *
 *  \endcode
 *
 *	Copyright (c) 2016, Jorge Lampérez. All rights reserved.
 */

#include <stdint.h>
#include "rpiservo.h"
#include "registers.h"
#include "../../config.h"

/**
*
* Set the ID for the current RPI servo.
*
* @param 	device_type
*
* @return	None.
*
* @note		None.
*
*/
void RPISERVO_setID(int device_type)
{
	/**todo*/
	set_device_type((uint16_t)device_type);
}
/**
*
* Set where the RPI servo is going to move in degrees 0 to 225 degrees.
*
* @param 	degrees.
*
* @return	None.
*
* @note		None.
*
*/
void RPISERVO_setGoal(int degrees)
{
	set_position((uint16_t)degrees*POT_RES_CONSTANT);
}
/**
*
* Set the minimum seek position for RPI servo in degrees.
*
* @param 	degrees.
*
* @return	None.
*
* @note		None.
*
*/
void RPISERVO_setCWLimit(int degrees)
{
	set_min_seek((uint16_t)degrees*POT_RES_CONSTANT);
}
/**
*
* Set the maximum seek position for the RPI servo.
*
* @param 	degrees.
*
* @return	None.
*
* @note		None.
*
*/
void RPISERVO_setCCWLimit(int degrees)
{
	set_max_seek((uint16_t)degrees*POT_RES_CONSTANT);
}
/**
*
* Set PID configuration parameters
*
* @param 	pgain.
* @param 	dgain.
* @param 	igain.
*
* @return	None.
*
* @note		None.
*
*/
void RPISERVO_setPIDconf(int pgain, int dgain)
{	/**todo*/
	set_pid_pgain((uint16_t)pgain);
	set_pid_dgain((uint16_t)dgain);
//	set_pid_igain((uint16_t)igain);
}
/**
*
* Get the RPI servo ID number.
*
* @return	ID.
*
* @note		None.
*
*/
int RPISERVO_getID()
{
	int id = get_device_type();
	return id;
}
/**
*
* Get current RPI servo position in degrees.
*
* @return	position in degrees.
*
* @note		None.
*
*/
float RPISERVO_getPosition()
{
	float position;
	position = get_position()/POT_RES_CONSTANT;
	return position;
}
/**
*
* Get the RPI servo temperature in ºC
*
* @return	temp.
*
* @note       http://ww1.microchip.com/downloads/en/DeviceDoc/20001942F.pdf
*             Sensor(MCP9701/9701A) transfer function:
* 			         VOUT = TC*TA+V0ºC -> TA = (VOUT - V0ºC)/TC
* 			  TA = Ambient Temperature
*             VOUT = Sensor Output Voltage
*             V0°C = Sensor Output Voltage at 0°C (400 mV)
*             TC = Temperature Coefficient (19.5 mV/°C)
*
*/
float RPISERVO_getTemp()
{
	float temp;
	temp = (get_temp()* ADC_RES_CONSTANT - 0.4) / 0.0195;
	return temp;
}
/**
*
* Get RPI servo battery level.
*
* @return	None.
*
* @note		None.
*
*/
float RPISERVO_getBattery()
{
	float battery;
	float battery = get_battery()* 3.7 * ADC_RES_CONSTANT;//3V3 rescaled 5??
	return battery;
}
/**
*
* Get RPI servo current level. Rsense and Rout scaled for 2A max.
*
* @return	None.
*
* @note		http://www.diodes.com/_files/datasheets/ZXCT1009.pdf
*           VSENSE = VSENSE+ - VSENSE- = VIN - VLOAD = ILOAD x RSENSE
*           VSENSE = VIN - VLOAD
*           VOUT = 0.01 x VSENSE x ROUT
*
*           ILOAD = VOUT/(RSENSE x ROUT x 0.01)
*
*           A 2A current is to be represented by a 5V output voltage.
*           E.g.
*           1) Choose the value of RSENSE to give 50mV > VSENSE > 500mV at full load.
*            For example VSENSE = 100mV at 2.0A.
*              RSENSE = 0.1/2.0 => 0.05Ω.
*            2) Choose ROUT to give VOUT = 5V, when VSENSE = 100mV.
*            Rearranging 1 for Rout gives:
*              ROUT = VOUT /(VSENSE x 0.01)
*              ROUT = 5 / (0.1 x 0.01) = 4.99KΩ
*
*           RSENSE = 0.05, ROUT = 4.99K.
*
*/
float RPISERVO_getCurrent()
{
	float current;
	current = (get_current() * ADC_RES_CONSTANT) / (0.05 * 4990 * 0.01);//ILOAD = VOUT/(RSENSExROUTx0.01)
	return current;
}
/**
*
* Difference between current and goal positions
*
* @return	None.
*
* @note		None.
*
*/
float RPISERVO_getError()
{
	float error;
	error = (get_position()-get_seek_position())/POT_RES_CONSTANT; //Pasarlo a grados.
	return 0;
}
/**
*
* Get velocity of the RPI servo.
*
* @return	None.
*
* @note		None.
*
*/

float RPISERVO_getVelocity()
{   /**todo*/
	return 0;
}
/**
*
* Get the minimum seek position for RPI servo in degrees.
*
* @param 	degrees.
*
* @return	None.
*
* @note		None.
*
*/
int RPISERVO_getCWLimit()
{
	int cw_limit;
	cw_limit = get_min_seek()/POT_RES_CONSTANT;
	return cw_limit;
}
/**
*
* Get the maximum seek position for the RPI servo.
*
* @param 	degrees.
*
* @return	None.
*
* @note		None.
*
*/
int RPISERVO_getCCWLimit()
{
	int ccw_limit;
	ccw_limit = get_max_seek()/POT_RES_CONSTANT;
	return ccw_limit;
}



