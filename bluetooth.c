#include <reg52.h>

#include <string.h>

#include "bluetooth.h"

#include "locomotion.h"

char bufferRX[30];
char bufferTX[30];

char i =0, j=0;
bit allowSend=0, msgBack=0, newComm=0;

/* initialize bluetooth */
void initBluetooth()
{
	initUart();
	init_serialInterrupt();
	memset(bufferRX,'\0',strlen(bufferRX));
	memset(bufferTX,'\0',strlen(bufferTX));
}

/* initialize serial interrupt */
void init_serialInterrupt()
{
	EA = 1; // enable all interrupts
	ES = 1; // enable serial interrupt
	RI = 0; // clear transfer flag
	TI = 0; // clear receive flag
}


/* initialize  UART */
void initUart()
{
	SCON = 0x50; /* serial communictaion in mode 1,	SM0 = 0,SM1=1
								*	serial receiver enabled	 REN = 1;
								*/	
	initBaud();   // initialize 9600 pulses per second baud rate

}

/* initialize baud rate*/
void initBaud()
{

	TMOD |= 0x20;  // timer one in mode 2, uses TH1,auto-reloads with TL1;
	TH1 = 0xfd;   // load timer with 253 thus it overflows at 9600 buad rate
	TL1 = 0xfd;   // reload with 253 on overflow
	TR1 = 1;	  	// start timer	

}



/* respond to bluetooth commands */
void responseBluetooth()
{
	if(newComm)
	{
		memset(bufferTX,'\0',strlen(bufferTX));

		if(!strcmp(bufferRX,"F#")) 	// car moves forward
		{
			goForward();
			strcpy(bufferTX,"Moving Forward#");
		}
		else if(!strcmp(bufferRX,"B#"))  //	car moves backward
		{
			goBackward();
			strcpy(bufferTX,"In Reverse Mode#");
		}
		else if(!strcmp(bufferRX,"L#"))  // car turns  left
		{
			turnLeft();
			strcpy(bufferTX,"Turning Left#");
		}
		else if(!strcmp(bufferRX,"R#"))  // car turns  right
		{
			turnRight();
			strcpy(bufferTX,"Turning Right");
		}
		else if(!strcmp(bufferRX,"SL#"))  // car slides  left
		{
			slideLeft();
			strcpy(bufferTX,"Sliding Left");
		}
		else if(!strcmp(bufferRX,"SR#"))  // car slides  left
		{
			slideRight();
			strcpy(bufferTX,"Sliding Right");
		}
		else if(!strcmp(bufferRX,"OL#"))  // car makes orange to the  left
		{
			orangeLeft();
			strcpy(bufferTX,"Orange to Left");
		}
		else if(!strcmp(bufferRX,"OR#"))  // car makes orange to the  right
		{
			orangeRight();
			strcpy(bufferTX,"Orange to Right");
		}
		else if(!strcmp(bufferRX,"S#"))  //stop car
		{
			stopCar();
			strcpy(bufferTX,"Car Parked#");
		}
		else if(!strcmp(bufferRX,"SU#"))  //speed up car
		{
			increSpeed();
			strcpy(bufferTX,"Car Speed Up#");
		}
		else if(!strcmp(bufferRX,"SD#"))  //speed down car
		{
			decreSpeed();
			strcpy(bufferTX,"Car Speed Down#");
		}
		else if(!strcmp(bufferRX,"L1#"))  //speed up car,  speed 1
		{
			setSpeed(0.1);
			strcpy(bufferTX,"Car Speed 1#");
		}
		else if(!strcmp(bufferRX,"L2#"))  //speed up car,  speed 2
		{
			setSpeed(0.2);
			strcpy(bufferTX,"Car Speed 2#");
		}
		else if(!strcmp(bufferRX,"L3#"))  //speed up car,  speed 3
		{
			setSpeed(0.3);
			strcpy(bufferTX,"Car Speed 3#");
		}
		else if(!strcmp(bufferRX,"L4#"))  //speed up car,  speed 4
		{
			setSpeed(0.4);
			strcpy(bufferTX,"Car Speed 4#");
		}
		else if(!strcmp(bufferRX,"L5#"))  //speed up car,  speed 5
		{
			setSpeed(0.5);
			strcpy(bufferTX,"Car Speed 5#");
		}
		else if(!strcmp(bufferRX,"L6#"))  //speed up car,  speed 6
		{
			setSpeed(0.6);
			strcpy(bufferTX,"Car Speed 6#");
		}
		else if(!strcmp(bufferRX,"L7#"))  //speed up car,  speed 7
		{
			setSpeed(0.7);
			strcpy(bufferTX,"Car Speed 7#");
		}
		else if(!strcmp(bufferRX,"L8#"))  //speed up car,  speed 8
		{
			setSpeed(0.8);
			strcpy(bufferTX,"Car Speed 8#");
		}
		else if(!strcmp(bufferRX,"L9#"))  //speed up car,  speed 9
		{
			setSpeed(0.9);
			strcpy(bufferTX,"Car Speed 9#");
		}
		else if(!strcmp(bufferRX,"LX#"))  //speed up car, xtreme speed
		{
			setSpeed(1);
			strcpy(bufferTX,"Car Speed X#");
		}
		else
		{
			strcpy(bufferTX,"Unknown Command: ");
			strcat(bufferTX,bufferRX);
		}
		memset(bufferRX,'\0',strlen(bufferRX));
		
		newComm = 0;
		
		TI = 1;
	}

}


void serial1() interrupt 4  /*Serial interrupt ISR*/
{
	char x;

	if(TI == 1)
	{
		if(msgBack)
		{
				if(!(bufferTX[j] == '\0'))
				{
					SBUF = bufferTX[j];
					j++;
				}
				else
				{
					msgBack = 0;
					j = 0;
				}
		}
		TI = 0;
	}
	else
	{
		x = SBUF;
		bufferRX[i++] = x;
		if(x == '#')
		{
			newComm = 1;
			msgBack = 1;
			i = 0;
		}
		
		RI = 0;
	}
}


	
	
	