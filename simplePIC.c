#include <xc.h>          // Load the proper header for the processor

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

void delay(void);
void sendPulse(void);

int main(void) {
  TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear
                         // bits 0 and 1 to zero, for output.  Others are inputs.
  LATFbits.LATF0 = 0;    // Turn LED1 on and LED2 off.  These pins sink current
  LATFbits.LATF1 = 1;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"
  LATDbits.LATD3 = 0;

  while(1) {
    //delay();
    LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
    sendPulse();
  }
  return 0;
}

void sendPulse(){
  int j;
  if (!PORTDbits.RD7) {
    // Pin D7 is the USER switch, low (FALSE) if pressed.
    LATDbits.LATD3 = 0;
    for (j = 0; j < 1000000; j++) {
    }
    LATDbits.LATD3 = 1;
    for (j = 0; j < 1000000; j++) {
    }
    LATDbits.LATD3 = 0;
  }
}

void delay(void) {
  int j;
  for (j = 0; j < 1000000; j++) { // number is 1 million
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}
