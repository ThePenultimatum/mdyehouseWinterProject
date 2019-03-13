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
  char message[MAX_MESSAGE_LENGTH];
  char message2[MAX_MESSAGE_LENGTH];
  uint32_t countVal = 0;
  char strToWrite[20];

  //U2MODEbits.ON = 1; // enabled uart2 for transfer of data to the xbee
  //U2MODEbits.UEN = 0b00; // only U2TX and U2RX used


  TRISD &= 0xFFF7;       // Bit 3 of TRISD is set to 0 to set it as digital output
                         // Use this pin 51 for output to send a pulse to the US sensor
  //TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear
                         // bits 0 and 1 to zero, for output.  Others are inputs.
  //LATFbits.LATF0 = 0;    // Turn LED1 on and LED2 off.  These pins sink current
  //LATFbits.LATF1 = 1;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"
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
    /*NU32_WriteUART3("0\r\n");                     // carriage return and newline
    NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);  // get message from computer
    NU32_WriteUART3(message);                  // send message back
    NU32_WriteUART3("\r\n");                     // carriage return and newline*/
    /*NU32_WriteUART3("Reading u2\r\n");
    NU32_ReadUART2(message2, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3(message2);
    NU32_WriteUART3("\r\n");*/
    //////////////////NU32_WriteUART2("Hello other xbee.\r\n");
    //delay();
    //countVal = sendPulse();

    //if (getTimeFromCount(count) > abs(BASELINE_DISTANCE - EPSILON)) {
    //  writeUart2(getFrame(count));
    //}
    //if (count != 2634039641) {
    //sprintf(strToWrite, "%u",count);//"%6.4f", count);
    //count = sendPulse();
    //if (count != 2634039641) {
      //sprintf(strToWrite, "%u",count);//"%6.4f", count);
    //sprintf(strToWrite, "%6.4f\r\n", ((float)countVal)*343/100000000);// PORTDbits.RD4);
    //NU32_WriteUART2(strToWrite);

    //////////////// Receiver code below
    char senderAddress[MAX_MESSAGE_LENGTH];
    char distanceString[MAX_MESSAGE_LENGTH];
    float distanceRead;

    NU32_ReadUART2(message, MAX_MESSAGE_LENGTH);

    sscanf(message, "%s %g", &senderAddress, &distanceRead);
    
    NU32_WriteUART3(message);
    NU32_WriteUART3("\r\n");
    NU32_WriteUART3(senderAddress);
    NU32_WriteUART3("\r\n");
    sprintf(distanceString, "%6.4f", distanceRead);
    NU32_WriteUART3(distanceString);
    NU32_WriteUART3("\r\n***\r\n");
    //////////////// Receiver code above

    //////////////// Sender code below
    /*delay();
    countVal = sendPulse();

    sprintf(strToWrite, "b %6.4f", ((float)countVal)*343/100000000);
    NU32_WriteUART2(strToWrite);
    NU32_WriteUART2("\r\n");*/
    //////////////// Sender code above

    //NU32_WriteUART2("a: 12324.2342");
    //NU32_WriteUART2(":\r\n");
    //NU32_WriteUART3(strToWrite);                  // send message back
    //NU32_WriteUART3("\r\n"); // carriage return and newline
    //NU32_WriteUART2("\r\n");
    /*NU32_WriteUART3("1\r\n");
    NU32_WriteUART2(message);
    NU32_WriteUART2("\r\n");
    NU32_WriteUART3("wrote message to uart2\r\n");
    NU32_ReadUART2(message2, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3("read message from uart2\r\n");
    NU32_WriteUART3(message2);
    NU32_WriteUART3("4\r\n");*/
    /*int t0 = 0;
    while(t0 < 80000000) {
      t0++;
    }
    t0 = 0;
    NU32_WriteUART2("+++");
    while(t0 < 80000000) {
      t0++;
    }
    t0 = 0;
    NU32_WriteUART3("Written to u2\r\n");
    NU32_ReadUART2(message2, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3(message2);
    NU32_WriteUART3("\r\n");
    NU32_WriteUART2("AT\r\n");
    while(t0 < 80000000) {
      t0++;
    }
    t0 = 0;
    //NU32_WriteUART2("ATID\r\n");
    NU32_WriteUART3("Written to u2\r\n");
    NU32_ReadUART2(message3, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3(message3);
    NU32_WriteUART3("\r\n");
    NU32_WriteUART2("ATDH 2222\r\n");
    while(t0 < 80000000) {
      t0++;
    }
    t0 = 0;
    NU32_WriteUART3("Written to u2\r\n");
    NU32_ReadUART2(message4, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3(message4);
    NU32_WriteUART3("\r\n");
    NU32_WriteUART2("ATDL 1111\r\n");
    while(t0 < 80000000) {
      t0++;
    }
    t0 = 0;
    NU32_WriteUART3("Written to u2\r\n");
    NU32_ReadUART2(message5, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3(message5);
    NU32_WriteUART3("\r\n");
    NU32_WriteUART2("ATCN\r\n");
    while(t0 < 80000000) {
      t0++;
    }
    t0 = 0;
    NU32_WriteUART3("Written to u2\r\n");
    NU32_ReadUART2(message6, MAX_MESSAGE_LENGTH);
    NU32_WriteUART3(message6);
    NU32_WriteUART3("\r\n");*/
  }
  return 0;
}