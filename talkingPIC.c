#include <stdio.h>
#include <xc.h>
#include "NU32.h"          // constants, funcs for startup and UART
#include "serial.h"

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

#define MAX_MESSAGE_LENGTH 200
#define WAITING 0
#define CORE_TICKS = 40000000 // number of core ticks in 1 second, 80 MHz

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

void delay(void);
unsigned int sendPulse(void);
unsigned int getCount(void);

int main(void) {
  NU32_Startup();
  char message[MAX_MESSAGE_LENGTH];
  unsigned int count = 0;
  char strToWrite[20];

  U2MODEbits.ON = 1; // enabled uart2 for transfer of data to the xbee
  U2MODEbits.UEN = 0b00; // only U2TX and U2RX used

  /*
  int xbee_ser_write( xbee_serial_t *serial, const void FAR *buffer,
    int length);
  int xbee_ser_putchar( xbee_serial_t *serial, uint8_t ch);
  int xbee_ser_rx_flush( xbee_serial_t *serial);
  int xbee_ser_open( xbee_serial_t *serial, uint32_t baudrate);
  int xbee_ser_baudrate( xbee_serial_t *serial, uint32_t baudrate);

  void writeUart2(const char * string) {
    while (*string != '\0') {
      while (U2STAbits.UTXBF) {
        ; // wait until tx buffer isn't full
      }
      U2TXREG = *string;
      ++string;
  }
  char *c getFrame(unsigned int count c);
}
  */


  TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear
                         // bits 0 and 1 to zero, for output.  Others are inputs.
  LATFbits.LATF0 = 0;    // Turn LED1 on and LED2 off.  These pins sink current
  LATFbits.LATF1 = 1;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"
  LATDbits.LATD3 = 0;
  
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
    //NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);  // get message from computer
    //delay();
    LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
    count = sendPulse();

    // if (getTimeFromCount(count) > abs(BASELINE_DISTANCE - EPSILON)) {
    //   writeUart2(getFrame(count));
    // }
    //if (count != 2634039641) {
      //sprintf(strToWrite, "%u",count);//"%6.4f", count);
    sprintf(strToWrite, "%6.4f", ((float)count)*343/CORE_TICKS);///1000000000);// PORTDbits.RD4);
    NU32_WriteUART3(strToWrite);                  // send message back
    NU32_WriteUART3("\r\n");                      // carriage return and newline
    NU32_LED1 = !NU32_LED1;                       // toggle the LEDs
    NU32_LED2 = !NU32_LED2;
    //}

  }
  return 0;
}

unsigned int sendPulse(){
  int j;
  unsigned int start, finish;
  unsigned int count = 0.0; // turn this into something where I am using the SYSCLK and getting time from freq and ticks

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
  int j;
  for (j = 0; j < 1000000; j++) { // number is 1 million
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}

unsigned int getCount(void){
  unsigned int start = 0, fin = 0;
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
