#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "myNU32.h"          // constants, funcs for startup and UART
#include "./libxbee3/include/xbee.h"
#include "ultrasonic.h"
//#include "./xbee_ansic_library/include/xbee/serial.h"

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

#define MAX_MESSAGE_LENGTH 200
#define WAITING 0
#define CORE_TICKS 40000000 // number of core ticks in 1 second, 80 MHz
#define MAXDIST 2.0

/*
define the x and y values of all 3 sensors here
then use them in calculation of distances

use a hash table for the node measurements?
*/

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

int32_t main(void) {

  NU32_Startup();

/*  __builtin_disable_interrupts();   // step 2: disable interrupts at CPU
  T2CONbits.TCKPS = 0b111;     // Timer2 prescaler N=64
  PR2 = 31249;              // period = (PR2+1) * N * 12.5 ns = 100 Hz
  TMR2 = 0;                // initial TMR2 count is 0
  IPC2bits.T2IP = 6;                // step 4: interrupt priority
  IFS0bits.T2IF = 0;                // step 5: clear T2 interrupt flag
  IEC0bits.T2IE = 1;                // step 6: enable timer2 interrupt
  T2CONbits.ON = 1;        // turn on Timer2
  __builtin_enable_interrupts();    // step 7: CPU interrupts enabled*/
  // interrupt stuff above

  // use at command +++ and get the remote id and then attach that to the
  // message written to the uart here with the distance
  __builtin_disable_interrupts();   // step 2: disable interrupts at CPU
/*  T2CONbits.TCKPS = 0b111;     // Timer2 prescaler N=64
  PR2 = 31249;              // period = (PR2+1) * N * 12.5 ns = 100 Hz
  TMR2 = 0;                // initial TMR2 count is 0
  IPC2bits.T2IP = 6;                // step 4: interrupt priority
  IFS0bits.T2IF = 0;                // step 5: clear T2 interrupt flag
  IEC0bits.T2IE = 1;                // step 6: enable timer2 interrupt
  T2CONbits.ON = 1;        // turn on Timer2*/
  /*IEC1bits.U2RXIE = 1;
  IEC1bits.U2TXIE = 0;
  U2STAbits.UTXEN = 0;
  IFS1bits.U2RXIF = 0;
  IFS1bits.U2TXIF = 0;
  IFS1bits.U2EIF = 0;
  IPC8bits.U2IP = 6;*/
  __builtin_enable_interrupts();    // step 7: CPU interrupts enabled

  char message[MAX_MESSAGE_LENGTH];
  char message2[MAX_MESSAGE_LENGTH];
  char senderAddress[MAX_MESSAGE_LENGTH];
  float distanceRead;
  uint32_t countVal = 0, j;
  char strToWrite[500];
  float xvalToUse;
  float yvalToUse;
  float outerx;
  float outery;
  static float x1 = 1.0; // x_a
  static float y1 = sqrt(3); // y_a
  static float x2 = 2.0; // x_b
  static float y2 = 0.0; // y_b
  static float x3 = 0.0; // x_c
  static float y3 = 0.0; // y_c
  volatile float r1 = 1.0; // r_a
  volatile float r2 = 1.0; // r_b
  volatile float r3 = 1.0; // r_c

  //TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  LATDbits.LATD3 = 0;
  
  while (1) {
    //NU32_WriteUART3("Reading uart2\r\n");
    NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);
    //NU32_WriteUART3(message);
    NU32_WriteUART3(message);
    NU32_WriteUART3("\r\n");
    sscanf(message, "%s %f", &senderAddress, &distanceRead);


    switch (senderAddress[0]) {
      case 'a': { // 1
        r1 = distanceRead;
        break;
      }
      case 'b': { // 2
        r2 = distanceRead;
        break;
      }
      case 'c': { // 3
        r3 = distanceRead;
        break;
      }
      default: {
        break;
      }
    }


    float a = (-2* x1 + 2 * x2);
    float b = (-2 * y1 + 2 * y2);
    float c = ((r1*r1) - (r2*r2) - (x1*x1) + (x2*x2) - (y1*y1) + (y2*y2));
    float d = (-2* x2 + 2 * x3);
    float e = (-2 * y2 + 2 * y3);
    float f = (r2*r2) - (r3*r3) - (x2*x2) + (x3*x3) - (y2*y2) + (y3*y3);
    float res = (c*e-f*b) / (e*a-b*d);
    float num = (c*e-f*b);
    float den = (e*a-b*d);
    float nump = c*e;
    float numn = f*b;
    float denp = e*a;
    float denn = b*d;
    float ynump = c*d;
    float ynumn = a*f;
    float ydenp = b*d;
    float ydenn = a*e;
    float trythisx = (nump - numn) / (denp - denn);
    float trythisy = (ynump - ynumn) / (ydenp - ydenn);
    outerx = (nump - numn) / (denp - denn);
    outery = (ynump - ynumn) / (ydenp - ydenn);

    sprintf(strToWrite, "Measured X value: %6.4f, Measured Y value:%6.4f\r\n",outerx,outery);
    NU32_WriteUART3(strToWrite);
  }
  return 0;
}
