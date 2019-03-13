#include <stdint.h>
#include <stdio.h>
#include "myNU32.h"          // constants, funcs for startup and UART
//#include "./libxbee3/include/xbee.h"
#include "ultrasonic.h"
//#include "./xbee_ansic_library/include/xbee/serial.h"

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

#define MAX_MESSAGE_LENGTH 200
#define WAITING 0
#define CORE_TICKS 40000000 // number of core ticks in 1 second, 80 MHz

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

int32_t main(void) {
  NU32_Startup();
  char message[MAX_MESSAGE_LENGTH];
  char message2[MAX_MESSAGE_LENGTH];
  uint32_t countVal = 0;
  char strToWrite[20];


  TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  LATDbits.LATD3 = 0;
  while (1) {

    //////////////// Receiver code below
    /*char senderAddress[MAX_MESSAGE_LENGTH];
    char distanceString[MAX_MESSAGE_LENGTH];
    float distanceRead;

    NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);

    sscanf(message, "%s %g", &senderAddress, &distanceRead);
    
    NU32_WriteUART3(message);
    NU32_WriteUART3("\r\n");
    NU32_WriteUART3(senderAddress);
    NU32_WriteUART3("\r\n");
    sprintf(distanceString, "%6.4f", distanceRead);
    NU32_WriteUART3(distanceString);
    NU32_WriteUART3("\r\n***\r\n");*/
    //////////////// Receiver code above

    //////////////// Sender code below
    delay();
    countVal = sendPulse();

    sprintf(strToWrite, "b %6.4f", ((float)countVal)*343/100000000);
    NU32_WriteUART2(strToWrite);
    NU32_WriteUART2("\r\n");
    //////////////// Sender code above
  }
  return 0;
}