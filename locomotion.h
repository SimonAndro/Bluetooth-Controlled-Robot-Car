
#include<reg52.h>

#ifndef LOCOMOTION_H_INCLUDED
#define LOCOMOTION_H_INCLUDED

/* Motor Drivers */
sbit front_IN1 = P2^0;   // left wheel
sbit front_IN2 = P2^1;   
sbit front_IN3 = P2^2;   // right wheel
sbit front_IN4 = P2^3; 

sbit back_IN1 = P2^4;    // left wheel
sbit back_IN2 = P2^5;   
sbit back_IN3 = P2^6;    // right wheel
sbit back_IN4 = P2^7; 

/*PWM output*/
sbit front_ENL = P1^0;
sbit front_ENR = P1^1;

sbit back_ENL = P1^2;
sbit back_ENR = P1^3;

enum motorStatus{forward=1, backward, stopped, leftTurn, rightTurn, leftSlide, rightSlide};

typedef struct Motion Motion;

struct Motion {
    float speed;
		int status;
		char isNewDir; 
};

extern Motion motionControl;

#define startSpeed 0.1

/* initialize car */
void initCar();

/* stop car motion*/
void stopCar();

/* car moves forward*/
void goForward();

/* car moves backward*/
void goBackward();

/* car turns left*/
void turnLeft();

/* car turns right*/
void turnRight();

/* car slides left*/
void slideLeft();

/* car slides right*/
void slideRight();

/* car makes an orange to the left*/
void orangeLeft();

/* car makes an orange to the right*/
void orangeRight();

/* increment speed */
void increSpeed();

/* increment speed */
void decreSpeed();

/* set speed level */
void setSpeed(float speedLevel);

/* run the car */
void runCar();

#endif // LOCOMOTION_H_INCLUDED
