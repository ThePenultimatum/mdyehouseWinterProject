#include <stdint.h>
#include <xc.h>
#include "myNU32.h"
#include "ultrasonic.h"

uint32_t sendPulse(){
  int j;
  uint32_t start, finish;
  uint32_t count = 0.0; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

  //if (!PORTDbits.RD7) {
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
  count = getCount();

    //finish = _CP0_GET_COUNT();
    //count = (float)((finish-start)*25/1000000000); // this just gives approx 0.1 sec
    // *25 gives time in nanoseconds, /1000,000,000 gives time in seconds
    // same as /40,000,000
    // assumes less than 2 * 1 cycle (107 sec each) has passed

  //}
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