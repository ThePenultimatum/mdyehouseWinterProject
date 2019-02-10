#include <stdio.h>
#include <xc.h>
#include "NU32.h"          // constants, funcs for startup and UART

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

#define MAX_MESSAGE_LENGTH 200
#define WAITING 0

void delay(void);
unsigned int sendPulse(void);

int main(void) {
  char message[MAX_MESSAGE_LENGTH];
  unsigned int count = 0;
  char strToWrite[20];

  TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear
                         // bits 0 and 1 to zero, for output.  Others are inputs.
  LATFbits.LATF0 = 0;    // Turn LED1 on and LED2 off.  These pins sink current
  LATFbits.LATF1 = 1;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"
  LATDbits.LATD3 = 0;
  
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
    //NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);  // get message from computer
    //delay();
    LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
    count = sendPulse();
    //if (count != 2634039641) {
      //sprintf(strToWrite, "%u",count);//"%6.4f", count);
    sprintf(strToWrite, "%u", PORTDbits.RD4);
    NU32_WriteUART3(strToWrite);                  // send message back
    NU32_WriteUART3("\r\n");                      // carriage return and newline
    NU32_LED1 = !NU32_LED1;                       // toggle the LEDs
    NU32_LED2 = !NU32_LED2;
    //}

  }
  return 0;
}

unsigned int sendPulse(){
  int j;
  unsigned int start, finish;
  float count = 0.0; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  if (!PORTDbits.RD7) {
    // Pin D7 is the USER switch, low (FALSE) if pressed.
    //LATDbits.LATD3 = 0;
    //WAITING = 1;
    //for (j = 0; j < 1000000; j++) {
    //for (j = 0; j < 400; j++) {
    //}
    //start = _CP0_GET_COUNT();
    LATDbits.LATD3 = 1;
    for (j = 0; j < 500; j++) {
      Nop();
    }
    LATDbits.LATD3 = 0;

    //finish = _CP0_GET_COUNT();
    //count = (float)((finish-start)*25/1000000000); // this just gives approx 0.1 sec
    // *25 gives time in nanoseconds, /1000,000,000 gives time in seconds
    // same as /40,000,000
    // assumes less than 2 * 1 cycle (107 sec each) has passed

  }
  return finish-start;
}

void delay(void) {
  int j;
  for (j = 0; j < 1000000; j++) { // number is 1 million
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}
