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

int32_t main(void) {

  NU32_Startup();

  // use at command +++ and get the remote id and then attach that to the
  // message written to the uart here with the distance


  char message[MAX_MESSAGE_LENGTH];
  char message2[MAX_MESSAGE_LENGTH];
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
    countVal = sendPulse();

    sprintf(strToWrite, "b:%6.4f", ((float)countVal)*343/100000000);
    NU32_WriteUART2(strToWrite);
    NU32_WriteUART2("\r\n");  
  }
  return 0;
}