#include <stdint.h>
#include <stdio.h>
#include "myNU32.h"          // constants, funcs for startup and UART
//#include "./libxbee3/include/xbee.h"
#include "trilateration.h"
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
  char senderAddress[MAX_MESSAGE_LENGTH];
  uint32_t senderId;
  char distanceString[MAX_MESSAGE_LENGTH];
  float distanceRead;
  float nodesDists[3];
  float xpos, ypos;
  float x0, y0, x1, y1, x2, y2;
  x0 = 1;
  x1 = 2;
  x2 = 3;
  y0 = 0;
  y1 = 3;
  y2 = 5;
  nodesDists[0] = 1;
  nodesDists[1] = 1;
  nodesDists[2] = 1;
  nodesDists[3] = 1;

  TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  LATDbits.LATD3 = 0;
  while (1) {

    //////////////// Receiver code below

    NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);

    sscanf(message, "%d %g", &senderId, &distanceRead);

    if ((senderId > 0) && (senderId < 4)) {
      nodesDists[senderId] = distanceRead;
      xpos = newX(x0, y0, nodesDists[1], x1, y1, nodesDists[2], x2, y2, nodesDists[3]);
      ypos = newY(x0, y0, nodesDists[1], x1, y1, nodesDists[2], x2, y2, nodesDists[3]);
      //NU32_WriteUART3(message);
      //NU32_WriteUART3("\r\n");
      sprintf(strToWrite, "x: %6.4f, y: %6.4f\r\n", xpos, ypos);
      //NU32_WriteUART3("Got new position\r\n");
      NU32_WriteUART3(strToWrite);
      NU32_WriteUART3("\r\n");
    }
    
    //NU32_WriteUART3(message);
    //NU32_WriteUART3("\r\n");
    //NU32_WriteUART3(senderAddress);
    //NU32_WriteUART3("\r\n");
    //sprintf(distanceString, "%6.4f", distanceRead);
    //NU32_WriteUART3(distanceString);
    //NU32_WriteUART3("\r\n***\r\n");
    //////////////// Receiver code above

    //////////////// Sender code below
    /*delay();
    countVal = sendPulse();

    sprintf(strToWrite, "b %6.4f", ((float)countVal)*343/100000000);
    NU32_WriteUART2(strToWrite);
    NU32_WriteUART2("\r\n");*/
    //////////////// Sender code above
  }
  return 0;
}