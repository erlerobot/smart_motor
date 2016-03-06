/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file timer.h 
 *  @brief Header for timer module.
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

#ifndef TIMER_H_
#define TIMER_H_ 1

/**
* 	Initialize timer.
*/
void TIMER_init(long long freq_nanosecs);

 #endif