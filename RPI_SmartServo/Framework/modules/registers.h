/**
 *  project  :  RPI_SmartServo          
 *  
 *  @file registers.h
 *  @brief Registers header
 * 
 *  @note 
 *
 *      none
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
 *  Copyright (c) 2016, Jorge Lampérez. All rights reserved.
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_ 1

#include<stdint.h>

void REGISTERS_init(void);
void REGISTERS_default(void);

//Setter methods
void set_device_type (uint8_t device_type);
void set_device_subtype (uint8_t device_subtype);
void set_flags (uint16_t flags);
void set_position (uint16_t position);
void set_velocity (uint16_t velocity);
void set_current (uint16_t current);
void set_battery (uint16_t battery);
void set_pwm_dir_a (uint8_t pwm_dir_a);
void set_pwm_dir_b (uint8_t pwm_dir_b);
void set_seek_position (uint16_t seek_position);
void set_seek_velocity (uint16_t seek_velocity);
void set_voltage (uint16_t voltage);
void set_pid_deadband (uint8_t pid_deadband);
void set_pid_pgain (uint16_t pid_pgain);
void set_pid_dgain (uint16_t pid_dgain);
void set_pid_igain (uint16_t pid_igain);
void set_min_seek (uint16_t min_seek);
void set_max_seek (uint16_t max_seek);
void set_reverse_seek (uint16_t reverse_seek);

//Getter methods
uint8_t get_device_type (void);
uint8_t get_device_subtype (void);
uint16_t get_flags (void);
uint16_t get_position (void);
uint16_t get_velocity (void);
uint16_t get_current (void);
uint16_t get_battery (void);
uint8_t get_pwm_dir_a (void);
uint8_t get_pwm_dir_b (void);
uint16_t get_seek_position (void);
uint16_t get_seek_velocity (void);
uint16_t get_voltage (void);
uint8_t get_pid_deadband (void);
uint16_t get_pid_pgain (void);
uint16_t get_pid_dgain (void);
uint16_t get_pid_igain (void);
uint16_t get_min_seek (void);
uint16_t get_max_seek (void);
uint16_t get_reverse_seek (void);


#endif
