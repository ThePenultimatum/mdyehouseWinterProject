#include <xc.h> 
#include "NU32.h"          // constants, funcs for startup and UART

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

#define MAX_MESSAGE_LENGTH 200

void delay(void);
int sendPulse(void);

int main(void) {
  char message[MAX_MESSAGE_LENGTH];
  int count = 0;
  char strToWrite[20];
  
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
    //NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);  // get message from computer
    //delay();
    LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
    count = sendPulse();
    strToWrite = sprintf(strToWrite, "%6.4f")
    NU32_WriteUART3(strToWrite);                     // send message back
    NU32_WriteUART3("\r\n");                      // carriage return and newline
    NU32_LED1 = !NU32_LED1;                       // toggle the LEDs
    NU32_LED2 = !NU32_LED2;

  }
  return 0;
}

// Load the proper header for the processor

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

int sendPulse(){
  int count = 0, j;
  if (!PORTDbits.RD7) {
    // Pin D7 is the USER switch, low (FALSE) if pressed.
    LATDbits.LATD3 = 0;
    for (j = 0; j < 1000000; j++) {
    }
    LATDbits.LATD3 = 1;
    for (j = 0; j < 1000000; j++) {
    }
    LATDbits.LATD3 = 0;
  }
  return count;
}

void delay(void) {
  int j;
  for (j = 0; j < 1000000; j++) { // number is 1 million
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}
