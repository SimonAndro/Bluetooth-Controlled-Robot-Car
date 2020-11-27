#ifndef BLUETOOTH_H_INCLUDED
#define BLUETOOTH_H_INCLUDED

/* Global variables*/

extern char bufferRX[30];
extern char bufferTX[30];

extern char i, j ;
extern bit allowSend, msgBack, newComm;


/* function prototypes*/

/*initialize bluetooth*/
void initBluetooth();

/* initialize UART */
void initUart();  			

/* initialize baudrate */
void initBaud();  			

/* initialize serial interrupt */
void init_serialInterrupt(); 

/* respond to bluetooth commands */
void responseBluetooth(); 

#endif // BLUETOOTH_H_INCLUDED
