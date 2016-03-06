/**
 *  project  : 	RPI_SmartServo			
 * 	
 * 	@file timer.c
 *  @brief Implementation for timer module.
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

#include "timer.h"
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "adc.h"

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)


sigset_t mask;

/**
*
*   Create the timer.
*
*   @param freq_nanosecs nanoseconds value.
*
*   @return	None.
*
*   @note		None.
*
*/
void TIMER_create(long long freq_nanosecs)
{ 
  timer_t timerid; 

	struct sigevent sev;
  struct itimerspec its;
   
   /* Create the timer */

   	sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIG;
    sev.sigev_value.sival_ptr = &timerid;

	if (timer_create(CLOCKID, &sev, &timerid) == -1)
        errExit("timer_create");

  printf("timer ID is 0x%lx\n", (long) timerid);

  its.it_value.tv_sec = freq_nanosecs / 1000000000;
  its.it_value.tv_nsec = freq_nanosecs % 1000000000;
  its.it_interval.tv_sec = its.it_value.tv_sec;
  its.it_interval.tv_nsec = its.it_value.tv_nsec;

  if (timer_settime(timerid, 0, &its, NULL) == -1)
         errExit("timer_settime");
}

/**
*
*   Timer signal handler.
*
*   @return None.
*
*   @note   None.
*
*/
void TIMER_signalHandler()
{
	struct sigaction sa;

	/* Establish handler for timer signal */

  printf("Establishing handler for signal %d\n", SIG);
   	
  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = ADC_handler;
  sigemptyset(&sa.sa_mask);
   
  if (sigaction(SIG, &sa, NULL) == -1)
        errExit("sigaction");
}
/**
*
*   Timer signal block.
*
*   @return None.
*
*   @note   None.
*
*/
void TIMER_signalBlock()
{
    /* Block timer signal temporarily */

   	printf("Blocking signal %d\n", SIG);
    
    sigemptyset(&mask);
    sigaddset(&mask, SIG);
    
    if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
        errExit("sigprocmask");
}
/**
*
*   Timer signal unblock.
*
*   @return None.
*
*   @note   None.
*
*/
void TIMER_signalUnblock()
{
	   /* Unlock the timer signal, so that timer notification
       can be delivered */

   printf("Unblocking signal %d\n", SIG);
    if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
        errExit("sigprocmask");
}
/** 
*
*   Initialize timer.
*
*   @param freq_nanosecs nanoseconds value.
*
*   @return None.
*
*   @note   None.
*
*/
void TIMER_init(long long freq_nanosecs)
{

	//Establish handler for timer signal.
	TIMER_signalHandler();
	//Block timer signal temporarily
	TIMER_signalBlock(&mask);
	//Timer Create
	TIMER_create(freq_nanosecs);
	//Unlock the timer signal
	TIMER_signalUnblock(&mask);

}
