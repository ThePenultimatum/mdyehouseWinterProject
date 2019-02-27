#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include "myNU32.h"
#include "ultrasonic.h"

uint32_t sendPulse(){
  int j;
  uint32_t start, finish;
  uint32_t count; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  LATDbits.LATD3 = 1;
  for (j = 0; j < 1000; j++) {
    Nop();
  }
  LATDbits.LATD3 = 0;
  count = getCount();
  char msg[20];
  sprintf(msg, "count:%6.4f\r\n", count);
  NU32_WriteUART3(msg);
  return count;
}

void delay(void) {
  int32_t j;
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
  return fin - start;
}