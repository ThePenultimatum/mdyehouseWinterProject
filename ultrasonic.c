#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include "myNU32.h"
#include "ultrasonic.h"

uint32_t sendPulse(){
  uint32_t start, finish, j;
  uint32_t count; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  LATDbits.LATD3 = 1;
  for (j = 0; j < 1000; j++) {
    Nop();
  }
  LATDbits.LATD3 = 0;
  count = getCount();
  //char msg[20];
  //sprintf(msg, "count:%6.4f\r\n", count);
  //NU32_WriteUART3(msg);
  return count;
}

/*uint32_t sendPulseToPin(uint32_t *latbitsPinPtr, uint32_t *portbitsPinPtr, uint32_t index){
  uint32_t start, finish, j;
  uint32_t count; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  *(latbitsPinPtr + index) = 1;
  for (j = 0; j < 1000; j++) {
    Nop();
  }
  *(latbitsPinPtr + index) = 0;
  count = getCountFromPin(portbitsPinPtr);
  //char msg[20];
  //sprintf(msg, "count:%6.4f\r\n", count);
  //NU32_WriteUART3(msg);
  return count;
}*/

uint32_t sendPulseToPinD3(void){
  uint32_t start, finish, j;
  uint32_t count; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  LATDbits.LATD3 = 1;
  for (j = 0; j < 1000; j++) {
    Nop();
  }
  LATDbits.LATD3 = 0;
  count = getCountFromPinD4();
  //char msg[20];
  //sprintf(msg, "count:%6.4f\r\n", count);
  //NU32_WriteUART3(msg);
  return count;
}

uint32_t sendPulseToPinD5(void){
  uint32_t start, finish, j;
  uint32_t count; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  LATDbits.LATD5 = 1;
  for (j = 0; j < 1000; j++) {
    Nop();
  }
  LATDbits.LATD5 = 0;
  count = getCountFromPinD6();
  //char msg[20];
  //sprintf(msg, "count:%6.4f\r\n", count);
  //NU32_WriteUART3(msg);
  return count;
}

uint32_t sendPulseToPinD8(void){
  uint32_t start, finish, j;
  uint32_t count; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  LATDbits.LATD8 = 1;
  for (j = 0; j < 1000; j++) {
    Nop();
  }
  LATDbits.LATD8 = 0;
  count = getCountFromPinD9();
  //char msg[20];
  //sprintf(msg, "count:%6.4f\r\n", count);
  //NU32_WriteUART3(msg);
  return count;
}

uint32_t sendPulseToPinD10(void){
  uint32_t start, finish, j;
  uint32_t count; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  LATDbits.LATD10 = 1;
  for (j = 0; j < 1000; j++) {
    Nop();
  }
  LATDbits.LATD10 = 0;
  count = getCountFromPinD11();
  //char msg[20];
  //sprintf(msg, "count:%6.4f\r\n", count);
  //NU32_WriteUART3(msg);
  return count;
}


void delay(void) {
  uint32_t j;
  for (j = 0; j < 1000000; j++) { // number is 1 million
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}

uint32_t getCount(void){
  uint32_t start = 0, fin = 0;
  while (!PORTDbits.RD4) {
    Nop();
    // watch out for getting caught in these loops if something gets interrupted
    // and then the switch happens quickly before this loop is entered... prevent this
  }
  start = _CP0_GET_COUNT();
  while (PORTDbits.RD4) {
    Nop();
  }
  fin = _CP0_GET_COUNT();
  char msg[20];
  //sprintf(msg, "fin-start:%d\r\n", fin-start);
  //NU32_WriteUART3(msg);
  return fin - start;
}

/*// portbitsPin is something like PORTDbits.RD4
uint32_t getCountFromPin(uint32_t *portbitsPinPtr, uint32_t index) {
  uint32_t start = 0, fin = 0;
  while (!(*(portbitsPinPtr + index)) {
    Nop();
    // watch out for getting caught in these loops if something gets interrupted
    // and then the switch happens quickly before this loop is entered... prevent this
  }
  start = _CP0_GET_COUNT();
  while (*portbitsPinPtr) {
    Nop();
  }
  fin = _CP0_GET_COUNT();
  char msg[20];
  //sprintf(msg, "fin-start:%d\r\n", fin-start);
  //NU32_WriteUART3(msg);
  return fin - start;
}*/

uint32_t getCountFromPinD4(void){
  uint32_t start = 0, fin = 0;
  while (!PORTDbits.RD4) {
    Nop();
    // watch out for getting caught in these loops if something gets interrupted
    // and then the switch happens quickly before this loop is entered... prevent this
  }
  start = _CP0_GET_COUNT();
  while (PORTDbits.RD4) {
    Nop();
  }
  fin = _CP0_GET_COUNT();
  char msg[20];
  //sprintf(msg, "fin-start:%d\r\n", fin-start);
  //NU32_WriteUART3(msg);
  return fin - start;
}

uint32_t getCountFromPinD6(void){
  uint32_t start = 0, fin = 0;
  while (!PORTDbits.RD6) {
    Nop();
    // watch out for getting caught in these loops if something gets interrupted
    // and then the switch happens quickly before this loop is entered... prevent this
  }
  start = _CP0_GET_COUNT();
  while (PORTDbits.RD6) {
    Nop();
  }
  fin = _CP0_GET_COUNT();
  char msg[20];
  //sprintf(msg, "fin-start:%d\r\n", fin-start);
  //NU32_WriteUART3(msg);
  return fin - start;
}

uint32_t getCountFromPinD9(void){
  uint32_t start = 0, fin = 0;
  while (!PORTDbits.RD9) {
    Nop();
    // watch out for getting caught in these loops if something gets interrupted
    // and then the switch happens quickly before this loop is entered... prevent this
  }
  start = _CP0_GET_COUNT();
  while (PORTDbits.RD9) {
    Nop();
  }
  fin = _CP0_GET_COUNT();
  char msg[20];
  //sprintf(msg, "fin-start:%d\r\n", fin-start);
  //NU32_WriteUART3(msg);
  return fin - start;
}

uint32_t getCountFromPinD11(void){
  uint32_t start = 0, fin = 0;
  while (!PORTDbits.RD11) {
    Nop();
    // watch out for getting caught in these loops if something gets interrupted
    // and then the switch happens quickly before this loop is entered... prevent this
  }
  start = _CP0_GET_COUNT();
  while (PORTDbits.RD11) {
    Nop();
  }
  fin = _CP0_GET_COUNT();
  char msg[20];
  //sprintf(msg, "fin-start:%d\r\n", fin-start);
  //NU32_WriteUART3(msg);
  return fin - start;
}

// numbers here taken from calibration data, that is in an image with chart and best fit line in images directory
float getDistFromCounts(uint32_t counts) {
  return (((float) counts) * 0.0000036 + 0.0431);
}