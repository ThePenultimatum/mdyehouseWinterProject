#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include "myNU32.h"          // constants, funcs for startup and UART
#include "./libxbee3/include/xbee.h"
//#include "./xbee_ansic_library/include/xbee/serial.h"

// Note this code is adapted from simplePIC.c from Northwestern University mechatronics ME-333 class

#define MAX_MESSAGE_LENGTH 200
#define WAITING 0
#define CORE_TICKS = 40000000 // number of core ticks in 1 second, 80 MHz

// #define BASELINE_DISTANCE = xxxxx;
// #define EPSILON_DISTANCE = xxxxx;

int32_t main(void) {
  NU32_Startup();
  char message[MAX_MESSAGE_LENGTH];
  char message2[MAX_MESSAGE_LENGTH];
  uint32_t count = 0;
  char strToWrite[20];

  //U2MODEbits.ON = 1; // enabled uart2 for transfer of data to the xbee
  //U2MODEbits.UEN = 0b00; // only U2TX and U2RX used

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
  
  //NU32_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {
    /////////////////////////////readUART2(message, MAX_MESSAGE_LENGTH);  // get message from computer
    //delay();
    //LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
    //count = sendPulse();

    // if (getTimeFromCount(count) > abs(BASELINE_DISTANCE - EPSILON)) {
    //   writeUart2(getFrame(count));
    // }
    //if (count != 2634039641) {
      //sprintf(strToWrite, "%u",count);//"%6.4f", count);
    //sprintf(strToWrite, "%6.4f", ((float)count)*343/CORE_TICKS);///1000000000);// PORTDbits.RD4);
    /*NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);  // get message from computer
    NU32_WriteUART3(message);                  // send message back
    NU32_WriteUART3("\r\n");                     // carriage return and newline
    NU32_WriteUART3("1\r\n");
    NU32_WriteUART2(message);
    NU32_WriteUART3("2\r\n");
    NU32_WriteUART2("\r\n");
    NU32_WriteUART3("3\r\n");*/
    NU32_ReadUART2(message2, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3("4\r\n");
    NU32_WriteUART2(message2);
    NU32_WriteUART3("5\r\n");
    //NU32_LED1 = !NU32_LED1;                       // toggle the LEDs
    //NU32_LED2 = !NU32_LED2;
    //}
    //writeUART2(message);
    //writeUART2("\r\n");
    //int32_t i = 0;
    //while (i < 20000000) {
    //  Nop();
    //}
    //char msg[20] = 0x7E000F00010013A20040522974003132333450;

  }
  return 0;
}

void delay(void) {
  int32_t j;
  for (j = 0; j < 1000000; j++) { // number is 1 million
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}