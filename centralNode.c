#include <stdint.h>
#include <stdio.h>
#include "myNU32.h"          // constants, funcs for startup and UART
#include "./libxbee3/include/xbee.h"
#include "ultrasonic.h"
//#include "./xbee_ansic_library/include/xbee/serial.h"

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

#define MAX_MESSAGE_LENGTH 200
#define WAITING 0
#define CORE_TICKS 40000000 // number of core ticks in 1 second, 80 MHz

/*
define the x and y values of all 3 sensors here
then use them in calculation of distances

use a hash table for the node measurements?
*/

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

int32_t main(void) {

  NU32_Startup();

  // use at command +++ and get the remote id and then attach that to the
  // message written to the uart here with the distance


  char message[MAX_MESSAGE_LENGTH];
  char message2[MAX_MESSAGE_LENGTH];
  char senderAddress[MAX_MESSAGE_LENGTH];
  float distanceRead;
  uint32_t countVal = 0, j;
  char strToWrite[20];

  TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  LATDbits.LATD3 = 0;
  
  while (1) {
    while (j < 400000) {
      j++;
      Nop();
    }
    //countVal = sendPulse();
    NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);
    sscanf(message, "%s: %6.4f", &senderAddress, &distanceRead);
    //
    NU32_WriteUART3("abc\r\n");
    //sscanf(message, "%s: %6.4f", &senderAddress, &distanceRead);
    //////////////// store these in hash table
    ///////// if certain conditions met, calculate a distance and print out where that is

    //sprintf(strToWrite, "b:%6.4f", ((float)countVal)*343/100000000);
    //NU32_WriteUART2(strToWrite); 
    //NU32_WriteUART2("\r\n");
  }
  return 0;
}
