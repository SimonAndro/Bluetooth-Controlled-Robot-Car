
#include "locomotion.h"

#include "bluetooth.h"

#include "speed_timer.h"

Motion motionControl; 


/* stop car motion*/
void stopCar()
{
	//set output pins
	front_IN1 = 0;
	front_IN2 = 0;
	front_IN3 = 0;
	front_IN4 = 0;
						  
	back_IN1  = 0;
	back_IN2  = 0;
	back_IN3  = 0;
	back_IN4  = 0;
	
	// update motion control
	motionControl.speed  = startSpeed;
	motionControl.status = stopped;
}

/* car moves forward*/
void goForward()
{
	if(motionControl.status == backward)
	{
		stopCar();
		stopCar();
		stopCar();
	}
	//set output pins
	front_IN1 = 1; // left tire 
	front_IN2 = 0;
	
	front_IN3 = 0; // right tire
	front_IN4 = 1;
	
	back_IN1 = 1; //  left tire 
  back_IN2 = 0;
	
	back_IN3 = 0; // right tire
  back_IN4 = 1;
	
	// update motion control
	motionControl.status = forward;
}

/* car moves backward*/
void goBackward()
{
	if(motionControl.status == forward)
	{
		stopCar();
		stopCar();
		stopCar();
	}
	
	//set output pins
	front_IN1 = 0; // left tire 
	front_IN2 = 1;
	
	front_IN3 = 1; // right tire
	front_IN4 = 0;
	 
	back_IN1 = 0; // left tire 
  back_IN2 = 1;
	
	back_IN3 = 1; // right tire
  back_IN4 = 0;
	
	// update motion control
	motionControl.status = backward;
}

/* car turns left*/
void turnLeft()
{
	
	//set output pins
	front_IN1 = 0; // left tire 
	front_IN2 = 0;
	
	front_IN3 = 0; // right tire
	front_IN4 = 1;
	
	back_IN1 = 0; //  left tire 
  back_IN2 = 0;
	
	back_IN3 = 0; // right tire
  back_IN4 = 1;
	
	// update motion control
	motionControl.status = leftTurn;
}

/* car turns right*/
void turnRight()
{
	front_IN1 = 1; // left tire 
	front_IN2 = 0;
	
	front_IN3 = 0; // right tire
	front_IN4 = 0;
	
	back_IN1 = 1; //  left tire 
  back_IN2 = 0;
	
	back_IN3 = 0; // right tire
  back_IN4 = 0;

	
	// update motion control
	motionControl.status = rightTurn;
	
}

/* car slides left*/
void slideLeft()
{
	front_IN1 = 0; // left tire 
	front_IN2 = 1;
	
	front_IN3 = 0; // right tire
	front_IN4 = 1;
	
	back_IN1 = 1; //  left tire 
  back_IN2 = 0;
	
	back_IN3 = 1; // right tire
  back_IN4 = 0;
	
	// update motion control
	motionControl.status = leftSlide;
}

/* car slides right*/
void slideRight()
{
	//set output pins
	
	front_IN1 = 1; // left tire 
	front_IN2 = 0;
	
	front_IN3 = 1; // right tire
	front_IN4 = 0;
	
	back_IN1 = 0; //  left tire 
  back_IN2 = 1;
	
	back_IN3 = 0; // right tire
  back_IN4 = 1;
	
	// update motion control
	motionControl.status = rightSlide;
}

/* car makes an orange to the left*/
void orangeLeft()
{
	//set output pins
	front_IN1 = 0; // left tire 
	front_IN2 = 1;
	
	front_IN3 = 0; // right tire
	front_IN4 = 1;
	
	back_IN1 = 0; //  left tire 
  back_IN2 = 1;
	
	back_IN3 = 0; // right tire
  back_IN4 = 1;
	
	// update motion control
	motionControl.status = leftSlide;
}

/* car makes an orange to the right*/
void orangeRight()
{
	front_IN1 = 1; // left tire 
	front_IN2 = 0;
	
	front_IN3 = 1; // right tire
	front_IN4 = 0;
	
	back_IN1 = 1; //  left tire 
  back_IN2 = 0;
	
	back_IN3 = 1; // right tire
  back_IN4 = 0;
	
	// update motion control
	motionControl.status = leftSlide;
}


/* increment speed */
void increSpeed()
{
	float newSpeed = motionControl.speed  + 0.1;
	
	motionControl.speed  = newSpeed > 1? 1.0 : newSpeed;
	restartSpeedTimer();
}

/* increment speed */
void decreSpeed()
{
	float newSpeed = motionControl.speed  - 0.1;
	
	motionControl.speed  = newSpeed < 0.1? 0.1 : newSpeed;
	restartSpeedTimer();
}

/* set speed level */
void setSpeed(float speedLevel)
{
		motionControl.speed  = speedLevel;
		restartSpeedTimer();

}

/* run the car */
void runCar()
{
	// reponse from bluetooth communication
	responseBluetooth(); 
	
	// Other jobs here
}

