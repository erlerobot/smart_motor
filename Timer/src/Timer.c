/*
 ============================================================================
 Name        : Timer.c
 Author      : Jorge
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "ads1115.h"

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)


sigset_t mask;

void ADC_handler(int sig, siginfo_t *si, void *uc) {
	static int cont=0;
	// POSITION (Potenciometer)
	uint16_t pos = ADS1115_readADC_singleEnded(POSITION_CHANNEL);
        uint16_t temp = ADS1115_readADC_singleEnded(TEMP_CHANNEL);
        uint16_t battery = ADS1115_readADC_singleEnded(BATTERY_CHANNEL);
        uint16_t current = ADS1115_readADC_singleEnded(CURRENT_CHANNEL);
	
        printf("ADS1115 pos: %d, temp: %d, battery: %d, current: %d \n", pos, temp, battery, current); 


	printf("handler %i \n", cont);
//	printf("Time: %d seconds\n", (double)clock());
	cont++;
}

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
#ifdef CONFIG_DEBUGGER
  printf("timer ID is 0x%lx\n", (long) timerid);
#endif
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
#ifdef CONFIG_DEBUGGER
  printf("Establishing handler for signal %d\n", SIG);
#endif
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
#ifdef CONFIG_DEBUGGER
   	printf("Blocking signal %d\n", SIG);
#endif
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
#ifdef CONFIG_DEBUGGER
   printf("Unblocking signal %d\n", SIG);
#endif
    if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
        errExit("sigprocmask");
}



int main(void) {

	long long freq_nanosecs= 10000000;//10ms
//	long long freq_nanosecs= 100000000;//100ms
//	long long freq_nanosecs= 1000000000;//1s

	ADS1115_init(ADS1115_ADDRESS);
	//Establish handler for timer signal.
	TIMER_signalHandler();
	//Block timer signal temporarily
	TIMER_signalBlock(&mask);
	//Timer Create
	TIMER_create(freq_nanosecs);
	//Unlock the timer signal
	TIMER_signalUnblock(&mask);

	while(1){

	}
}
