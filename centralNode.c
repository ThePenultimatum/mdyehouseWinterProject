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
/////////////////////////////////////////////////////////////////////////////////////////////////
static float x1 = 0.0;
static float y1 = 0.0;
static float x2 = 2.0;
static float y2 = 0.0;
static float x3 = 1;
static float y3 = sqrt(3);
volatile float r1 = 1.0;
volatile float r2 = 1.0;
volatile float r3 = 1.0;
float latestX = 12.0;
float latestY = 12.0;

/*
define the x and y values of all 3 sensors here
then use them in calculation of distances

use a hash table for the node measurements?
*/

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

/*void __ISR(_UART_2_VECTOR, IPL6SOFT) Controller(void) { 
  // _TIMER_2_VECTOR = 8

  static int counter = 0; // initialize counter once
  char message[MAX_MESSAGE_LENGTH];
  char message2[MAX_MESSAGE_LENGTH];
  char senderAddress[MAX_MESSAGE_LENGTH];
  float distanceRead;
  uint32_t countVal = 0, j;
  char strToWrite[20];

  NU32_WriteUART3("def\r\n");
  //countVal = sendPulse();
  NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);
  NU32_WriteUART3("ghi\r\n");
  //sscanf(message, "%s: %6.4f", &senderAddress, &distanceRead);
  //
  NU32_WriteUART3(message);
  NU32_WriteUART3("\r\n");
  NU32_WriteUART3("jkl\r\n");
  //OC1RS = Waveform[counter];
  //counter++; // add one to counter every time ISR is entered
  //if (counter == NUMSAMPS) {
  //  counter = 0; // roll the counter over when needed
  //}
  //char strToWrite[20];
  //uint32_t countVal = 0;

  //countVal = sendPulse();

  //sprintf(strToWrite, "b:%6.4f", ((float)countVal)*343/100000000);
  //NU32_WriteUART2(strToWrite);
  //NU32_WriteUART2("\r\n");  

  IFS0bits.T2IF = 0;                // ste
}*/

/*void __ISR(_UART_2_VECTOR, IPL6SOFT) IntUart2Handler(void) { 
  char message[MAX_MESSAGE_LENGTH];
  if (IFS1bits.U2RXIF) {
    NU32_WriteUART3("RX interrupt\r\n");
    NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3(message);
    IFS1bits.U2RXIF = 0;
  } else if (IFS1bits.U2TXIF) {
    NU32_WriteUART3("TX interrupt\r\n");
    IFS1bits.U2TXIF = 0;
  } else if (IFS1bits.U2EIF) {
    NU32_WriteUART3("Uart error interrupt\r\n");
    //U2STAbits.OERR = 0;
    IFS1bits.U2EIF = 0;
  }

  IFS1bits.U2EIF = 0;
}*/

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

  //TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  LATDbits.LATD3 = 0;
  
  while (1) {
    //NU32_WriteUART3("Reading uart2\r\n");
    NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);
    //NU32_WriteUART3(message);
    NU32_WriteUART3(message);
    NU32_WriteUART3("\r\n");
    r1 = 1.155;
    r2 = 1.155;
    r3 = 1.155;
    sscanf(message, "%s %f", &senderAddress, &distanceRead);


    switch (senderAddress[0]) {
      case '1': {
        r1 = distanceRead;
        break;
      }
      case '2': {
        r2 = distanceRead;
        break;
      }
      case '3': {
        r3 = distanceRead;
        break;
      }
      default: {
        break;
      }
    }


    latestX = newXVal(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    latestY = newYVal(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    sprintf(strToWrite, "latestX: %6.4f\r\n", newXVal(x1,y1,r1,x2,y2,r2,x3,y3,r3));
    NU32_WriteUART3(strToWrite);
    sprintf(strToWrite, "latestY: %6.4f\r\n", newYVal(x1,y1,r1,x2,y2,r2,x3,y3,r3));
    NU32_WriteUART3(strToWrite);
        sprintf(strToWrite, "senderAddress,distanceRead: %s, %6.4f, r1: %6.4f, r2: %6.4f, r3: %6.4f\r\n", senderAddress, distanceRead, r1, r2, r3);
    NU32_WriteUART3(strToWrite);
    latestX = newXVal(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    sprintf(strToWrite, "latestXSet: %6.4f\r\n", (float) (int) latestX);
    NU32_WriteUART3(strToWrite);
    latestY = newYVal(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    sprintf(strToWrite, "latestYSet: %6.4f\r\n", (float) (int) latestY);
    NU32_WriteUART3(strToWrite);
    xvalToUse = newXVal(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    sprintf(strToWrite, "latestXSet: %6.4f\r\n", (int) newXVal(x1,y1,r1,x2,y2,r2,x3,y3,r3));
    NU32_WriteUART3(strToWrite);
    yvalToUse = newYVal(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    sprintf(strToWrite, "latestYSet: %6.4f\r\n", (int) newYVal(x1,y1,r1,x2,y2,r2,x3,y3,r3));
    NU32_WriteUART3(strToWrite);

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
    float outerx = (nump - numn) / (denp - denn);
    float outery = (ynump - ynumn) / (ydenp - ydenn);

    sprintf(strToWrite, "a:%f, b:%f, c:%f, d:%f, e:%f, f:%f, nump:%f, numn:%f, denp:%f, denn:%f top:%f, bot:%f, manually:%f, trythisx:%f, outerx:%f\r\n", a,b,c,d,e,f, nump, numn, denp, denn, (nump - numn), (denp - denn), ((nump - numn) / (denp - denn)), trythisx, outerx);
    NU32_WriteUART3(strToWrite);


    //delay();
    //delay();
    //r1 = 1.155;
    //r2 = 1.155;
    //r3 = 1.155;
    // float a = (-2* x1 + 2 * x2);
    // float b = (-2 * y1 + 2 * y2);
    // float c = ((r1*r1) - (r2*r2) - (x1*x1) + (x2*x2) - (y1*y1) + (y2*y2));
    // float d = (-2* x2 + 2 * x3);
    // float e = (-2 * y2 + 2 * y3);
    // float f = (r2*r2) - (r3*r3) - (x2*x2) + (x3*x3) - (y2*y2) + (y3*y3);
    // float res = (c*e-f*b) / (e*a-b*d);
    // float num = (c*e-f*b);
    // float den = (e*a-b*d);
    // float nump = c*e;
    // float numn = f*b;
    // float denp = e*a;
    // float denn = b*d;
    // latestX = newXVal(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    // latestY = newYVal(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    // sprintf(strToWrite, "newX: %6.4f, d:%d, f:%f, orig:%f\r\n", latestX, (int) latestX, latestX, newXVal(x1,y1,r1,x2,y2,r2,x3,y3,r3));
    // NU32_WriteUART3(strToWrite);
    // sprintf(strToWrite, "a:%f, b:%f, c:%f, d:%f, e:%f, f:%f, res:%f, nump:%f, numn:%f, denp:%f, denn:%f\r\n", a,b,c,d,e,f,res, nump, numn, denp, denn);
    // NU32_WriteUART3(strToWrite);


    //this is messing up the baud////////////////////////////////////

    // switch (senderAddress[0]) {
    //   case '1': {
    //     r1 = distanceRead;
    //   }
    //   case '2': {
    //     r2 = distanceRead;
    //   }
    //   case '3': {
    //     r3 = distanceRead;
    //   }
    //   default: {
    //   }
    // }

    // if ((r1 < MAXDIST) && (r2 < MAXDIST) && (r3 < MAXDIST)) {
    //   latestX = newX(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    //   latestY = newY(x1,y1,r1,x2,y2,r2,x3,y3,r3);
    //   //sprintf(strToWrite, "senderAddress: %c\r\n", senderAddress[0]);
    //   //NU32_WriteUART3(strToWrite);
    //   //sprintf(strToWrite, "distanceRead: %6.4f\r\n", distanceRead);
    //   //NU32_WriteUART3(strToWrite);
    //   //sprintf(strToWrite, "newX: %6.4f, newY: %6.4f\r\n", latestX, latestY);
    //   //NU32_WriteUART3(strToWrite);
    // }

    /*while (j < 40000) {
      j++;
      Nop();
    }*/

    /*NU32_WriteUART3("*********************\r\n");

    sprintf(strToWrite, "Contains data flag %d\r\n", U2STAbits.URXDA);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "When interrupts are generated flag %d\r\n", U2STAbits.URXISEL);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "No Pending transmission in TX buffer flag %d\r\n", U2STAbits.TRMT);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "Transmit buffer full flag %d\r\n", U2STAbits.UTXBF);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "Transmissions enabled flag %d\r\n", U2STAbits.UTXEN);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "Recieving enabled flag %d\r\n", U2STAbits.URXEN);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "RX flag %d\r\n", IFS1bits.U2RXIF);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "TX flag %d\r\n", IFS1bits.U2TXIF);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "E flag %d\r\n", IFS1bits.U2EIF);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "OERR flag %d\r\n", U2STAbits.OERR);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "FERR flag %d\r\n", U2STAbits.FERR);
    NU32_WriteUART3(strToWrite);

    sprintf(strToWrite, "PERR flag %d\r\n", U2STAbits.PERR);
    NU32_WriteUART3(strToWrite);

    NU32_WriteUART3("************************\r\n");*/
    //countVal = sendPulse();
    //NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);
    //sscanf(message, "%s: %6.4f", &senderAddress, &distanceRead);
    //
    //NU32_WriteUART3(message);
    //NU32_WriteUART3("\r\n");
    //sscanf(message, "%s: %6.4f", &senderAddress, &distanceRead);
    //////////////// store these in hash table
    ///////// if certain conditions met, calculate a distance and print out where that is

    //sprintf(strToWrite, "b:%6.4f", ((float)countVal)*343/100000000);
    //NU32_WriteUART2(strToWrite); 
    //NU32_WriteUART2("\r\n");
  }
  return 0;
}
