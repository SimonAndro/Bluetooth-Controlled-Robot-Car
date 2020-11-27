#include <reg52.h>

#include "speed_timer.h"

#include "locomotion.h"


char tMonitor = 0;   // timer monitor, monitor how many many times the timer has overflown

void init_timer_0()
{
	/*
	*initializing the timer zero 
	*in the 16 bit timing mode
	*/
	TMOD |= 0x01; /**last four bits of TMOD set mode for timer zero to 0001	
				  **last 2 bits ie 01 sets mode to a 16 bit counter
				  **the third bit from the left sets mode to a timer rather
			   	  	than a counter
				  **fourth bit sets the mode to start timer on effect of
				  **TRO rather than adding a constraint from the 
				  	the external interrupt
				  */
	TH0 = (65536-TIMERRELOAD)/256;		// timer start value in the upper 8 bits	
	TL0 = (65536-TIMERRELOAD)%256;		// timer start value in the lower 8 bits
	
	EA = 1;  // enable overall interruption
	ET0 = 1; // enable timer zero  interruption
	TR0 = 1; // start timer zero 
	/***/
}

// restart speed timer
void restartSpeedTimer()
{
	tMonitor = 0;
}

void timerInterrupt_0() interrupt 1 // timer zero interruption code
{	
	tMonitor++; // tMonitor equals 1 at 20us

	// turn off
	if(tMonitor == (int)(TIMERPERIOD*motionControl.speed))
	{
		front_ENL =  0;
		front_ENR =  0;

		back_ENL =   0;
		back_ENR =   0;
	}
		
	// reset timer
	if(tMonitor == TIMERPERIOD)
	{
		tMonitor = 0;
		
		front_ENL =  1;
		front_ENR =  1;

		back_ENL  =  1;
		back_ENR  =  1;
	}

	/*initialize the timer registers again*/
	TH0 = (65536-TIMERRELOAD)/256;		// timer start value in the upper 8 bits	
	TL0 = (65536-TIMERRELOAD)%256;		// timer start value in the lower 8 bits
}
	
	