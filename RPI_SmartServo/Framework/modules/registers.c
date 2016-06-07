/**
 *  project  :  RPI_SmartServo          
 *  
 *  @file registers.c
 *  @brief Registers implementation
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


#include "registers.h"
#include <stdint.h>
//Device type
static uint8_t REG_device_type;
//Device subtype
static uint8_t REG_device_subtype;
//Flags
static uint16_t REG_flags;
//Position
static uint16_t REG_position;
//Velocity
static uint16_t REG_velocity;
//Current
static uint16_t REG_current;
//Battery
static uint16_t REG_battery;
//PWM_DIRA
static uint8_t REG_pwm_dir_a;
//PWM_DIRB
static uint8_t REG_pwm_dir_b;
//Seek position
static uint16_t REG_seek_position;
//Seek velocity
static uint16_t REG_seek_velocity;
//Temperature
static uint16_t REG_temp;
//PID deadband
static uint8_t REG_pid_deadband;
//PID PGAIN
static uint16_t REG_pid_pgain;
//PID DGAIN
static uint16_t REG_pid_dgain;
//PID IGAIN
static uint16_t REG_pid_igain;
//Min Seek
static uint16_t REG_min_seek;
//Max Seek
static uint16_t REG_max_seek;
//Reverse Seek
static uint8_t REG_reverse_seek; 

void REGISTERS_init(int16_t position)
{
	set_seek_position(position);
	set_seek_velocity(0);
}

void REGISTERS_default(void)
{
	set_seek_position(0);
	set_seek_velocity(0);
}

//Setter methods
void set_device_type (uint8_t device_type)
{
	//lock (*id_mutex_global)
  REG_device_type = device_type;
  //unlock ()
}

void set_device_subtype (uint8_t device_subtype)
{
  REG_device_subtype = device_subtype;
}

void set_flags (uint16_t flags)
{
  REG_flags = flags;
}

void set_position (uint16_t position)
{
  REG_position = position;
}

void set_velocity (uint16_t velocity)
{
  REG_velocity = velocity;
}

void set_current (uint16_t current)
{
  REG_current = current;
}
void set_battery (uint16_t battery)
{
  REG_battery = battery;
}

void set_pwm_dir_a (uint8_t pwm_dir_a)
{
  REG_pwm_dir_a = pwm_dir_a;
}

void set_pwm_dir_b (uint8_t pwm_dir_b)
{
  REG_pwm_dir_b = pwm_dir_b;
}

void set_seek_position (uint16_t seek_position)
{
  REG_seek_position = seek_position;
}

void set_seek_velocity (uint16_t seek_velocity)
{
  REG_seek_velocity = seek_velocity;
}

void set_temp (uint16_t temp)
{
  REG_temp = temp;
}

void set_pid_deadband (uint8_t pid_deadband)
{
  REG_pid_deadband = pid_deadband;
}

void set_pid_pgain (uint16_t pid_pgain)
{
  REG_pid_pgain = pid_pgain;
}

void set_pid_dgain (uint16_t pid_dgain)
{
  REG_pid_dgain = pid_dgain;
}

void set_pid_igain (uint16_t pid_igain)
{
  REG_pid_igain = pid_igain;
}

void set_min_seek (uint16_t min_seek)
{
  REG_min_seek = min_seek;
}

void set_max_seek (uint16_t max_seek)
{
  REG_max_seek = max_seek;
}

void set_reverse_seek (uint16_t reverse_seek)
{
  REG_reverse_seek = reverse_seek;
}

//Getter methods

uint8_t get_device_type (void)
{
  return REG_device_type;
}

uint8_t get_device_subtype (void)
{
 return REG_device_subtype;
}

uint16_t get_flags (void)
{
  return REG_flags;
}

uint16_t get_position (void)
{
  return REG_position;
}

uint16_t get_velocity (void)
{
  return REG_velocity;
}

uint16_t get_current (void)
{
  return REG_current;
}
uint16_t get_battery (void)
{
  return REG_battery;
}

uint8_t get_pwm_dir_a (void)
{
  return REG_pwm_dir_a;
}

uint8_t get_pwm_dir_b (void)
{
  return REG_pwm_dir_b;
}

uint16_t get_seek_position (void)
{
  return REG_seek_position;
}

uint16_t get_seek_velocity (void)
{
  return REG_seek_velocity;
}

uint16_t get_temp (void)
{
  return REG_temp;
}

uint8_t get_pid_deadband (void)
{
  return REG_pid_deadband;
}

uint16_t get_pid_pgain (void)
{
  return REG_pid_pgain;
}

uint16_t get_pid_dgain (void)
{
  return REG_pid_dgain;
}

uint16_t get_pid_igain (void)
{
  return REG_pid_igain;
}

uint16_t get_min_seek (void)
{
  return REG_min_seek;
}

uint16_t get_max_seek (void)
{
  return REG_max_seek;
}

uint16_t get_reverse_seek (void)
{
  return REG_reverse_seek;
}
