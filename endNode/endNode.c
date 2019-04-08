// #include <stdint.h>
// #include <stdio.h>
// #include "myNU32.h"          // constants, funcs for startup and UART
// #include "./libxbee3/include/xbee.h"
// #include "ultrasonic.h"
// #include "xbeeInterfacing.h"
// //#include "./xbee_ansic_library/include/xbee/serial.h"

// // Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

// //#define MAX_MESSAGE_LENGTH 200
// //#define WAITING 0
// //#define CORE_TICKS 40000000 // number of core ticks in 1 second, 80 MHz

// //volatile int backgroundDist = 100;

// /*
// store avg background values here

// */

// // #define BASELINE_DISTANCE = xxxxx;
// // #define EPSILON_DISTANCE = xxxxx;
// /*
// int32_t main(void) {

//   NU32_Startup();

//   // use at command +++ and get the remote id and then attach that to the
//   // message written to the uart here with the distance

//   char myAddress[MAX_MESSAGE_LENGTH];
//   //getXBeePropertyAT(myAddress, "ATMY");
//   //NU32_WriteUART2(myAddress);
//   //NU32_WriteUART2(": my address\r\n");
//   char message[MAX_MESSAGE_LENGTH];
//   char message2[MAX_MESSAGE_LENGTH];
//   uint32_t countVal = 0, j;
//   float dist;
//   char strToWrite[20];

//   TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
//                          // Use this pin 51 for output to send a pulse to the US sensor
//   LATDbits.LATD3 = 0;
  
//   while (1) {
//     while (j < 400000) {
//       j++;
//       Nop();
//     }
//     countVal = sendPulse();
//     dist = ((float)countVal)*343/100000000;
//     if (dist < backgroundDist) {
//       sprintf(strToWrite, "b:%6.4f", ((float)countVal)*343/100000000);
//       NU32_WriteUART2(strToWrite); 
//       NU32_WriteUART2("\r\n");
//     }
//   }
//   return 0;
// }
// */


// //#include <stdint.h>
// //#include <stdio.h>
// //#include "myNU32.h"          // constants, funcs for startup and UART
// //#include "./libxbee3/include/xbee.h"
// //#include "ultrasonic.h"
// //#include "./xbee_ansic_library/include/xbee/serial.h"

// // Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

// #define MAX_MESSAGE_LENGTH 200
// #define WAITING 0
// #define CORE_TICKS 40000000 // number of core ticks in 1 second, 80 MHz

// // #define BASELINE_DISTANCE = xxxxx;
// // #define EPSILON_DISTANCE = xxxxx;

// /*void __ISR(_TIMER_2_VECTOR, IPL5SOFT) Controller(void) { // _TIMER_2_VECTOR = 8
//   static int counter = 0; // initialize counter once

//   //OC1RS = Waveform[counter];
//   //counter++; // add one to counter every time ISR is entered
//   //if (counter == NUMSAMPS) {
//   //  counter = 0; // roll the counter over when needed
//   //}
//   char strToWrite[20];
//   uint32_t countVal = 0;

//   countVal = sendPulse();

//   sprintf(strToWrite, "b:%6.4f", ((float)countVal)*343/100000000);
//   NU32_WriteUART2(strToWrite);
//   NU32_WriteUART2("\r\n");  

//   IFS0bits.T2IF = 0;                // step 5: clear T2 interrupt flag
// }*/


// int32_t main(void) {

//   NU32_Startup();

//   __builtin_disable_interrupts();   // step 2: disable interrupts at CPU
//   /*T2CONbits.TCKPS = 0b100;     // Timer2 prescaler N=16 (1:1)
//   PR2 = 4999;              // period = (PR2+1) * N * 12.5 ns = 1000 us, 1 kHz
//   TMR2 = 0;                // initial TMR2 count is 0
//   IPC2bits.T2IP = 5;                // step 4: interrupt priority
//   IFS0bits.T2IF = 0;                // step 5: clear T2 interrupt flag
//   IEC0bits.T2IE = 1;                // step 6: enable timer2 interrupt
//   T2CONbits.ON = 1;        // turn on Timer2*/
//   __builtin_enable_interrupts();    // step 7: CPU interrupts enabled
//   // interrupt stuff above


//   // use at command +++ and get the remote id and then attach that to the
//   // message written to the uart here with the distance


//   char message[MAX_MESSAGE_LENGTH];
//   char message2[MAX_MESSAGE_LENGTH];
//   uint32_t countVal = 0;
//   uint32_t j;
//   char strToWrite[20];

//   TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
//                          // Use this pin 51 for output to send a pulse to the US sensor
//   LATDbits.LATD3 = 0;
  
//   while (1) {
//     j = 0;
//     while (j < 400000) {
//       j++;
//       Nop();
//     }
//     //countVal = sendPulse();

//     //sprintf(strToWrite, "b:%6.4f", ((float)countVal)*343/100000000);
//     //NU32_WriteUART2(strToWrite);
//     //NU32_WriteUART2("\r\n");  
//     countVal = sendPulse();

//     sprintf(strToWrite, "b:%6.4f", ((float)countVal)*343/100000000);
//     NU32_WriteUART2(strToWrite);
//     NU32_WriteUART2("\r\n");  
//   }
//   return 0;
// }

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

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

int32_t minInt(int32_t a, int32_t b) {
  if (b < a) {
    return b;
  }
  return a;
}

int32_t main(void) {

  NU32_Startup();

  // use at command +++ and get the remote id and then attach that to the
  // message written to the uart here with the distance


  char message[MAX_MESSAGE_LENGTH];
  char message2[MAX_MESSAGE_LENGTH];
  //uint32_t countVal = 0, j;
  uint32_t countVal = 0, countVal0 = 0, countVal1 = 0, countVal2 = 0, countVal3 = 0, j;
  char strToWrite[20];

  //TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 D3 for output to send a pulse to the US sensor
                         // with additional 3 sensors, use D5 pin 53, D8 pin 42, D10 pin 44 as output as well
                         // Another method could be to use the same output pin but wait
                         // beyond an expected time for measurement
  TRISD &= 0xFAD7;
  LATDbits.LATD3 = 0;
  LATDbits.LATD5 = 0;
  LATDbits.LATD8 = 0;
  LATDbits.LATD10 = 0;
  
  while (1) {
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < 40000000) {
      ;
    }
    // countVal0 = sendPulseToPin(&(LATDbits.LATD3), &(LATDbits.LATD4));
    // countVal1 = sendPulseToPin(&(LATDbits.LATD5), &(LATDbits.LATD6));
    // countVal2 = sendPulseToPin(&(LATDbits.LATD8), &(LATDbits.LATD9));
    // countVal3 = sendPulseToPin(&(LATDbits.LATD10), &(LATDbits.LATD11));
    countVal0 = sendPulseToPinD3();
    countVal1 = sendPulseToPinD5();
    countVal2 = sendPulseToPinD8();
    countVal3 = sendPulseToPinD10();

    countVal = minInt(minInt(minInt(countVal0, countVal1), countVal2), countVal3);//minInt(countVal0, countVal0);//minInt(minInt(minInt(countVal0, countVal1), countVal2), countVal3);

    sprintf(strToWrite, "b:%6.4f", getDistFromCounts(countVal));
    NU32_WriteUART2(strToWrite);
    NU32_WriteUART2("\r\n");  
  }
  return 0;
}