#include "locomotion.h"

#include "bluetooth.h"

#include "speed_timer.h"

/* helper functions prototypes */
void initCar();

/* main function */
void main()
{
	initCar();
	while(1)
	{
		runCar();
	}
}

/* helper functions */
void initCar( )
{
	// initialize car in parked state
	stopCar();
	
	// initial car speed
	motionControl.speed  = startSpeed;
	
	// initialize bluetooth communication
	initBluetooth();
	
	// initialize speed timer
	init_timer_0();
}


