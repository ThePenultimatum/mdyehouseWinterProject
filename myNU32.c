#include <stdio.h>
#include "myNU32.h"

// Device Configuration Registers
// These only have an effect for standalone programs but don't harm bootloaded programs.
// the settings here are the same as those used by the bootloader
#pragma config DEBUG = OFF          // Background Debugger disabled
#pragma config FWDTEN = OFF         // WD timer: OFF
#pragma config WDTPS = PS4096       // WD period: 4.096 sec
#pragma config POSCMOD = HS         // Primary Oscillator Mode: High Speed crystal
#pragma config FNOSC = PRIPLL       // Oscillator Selection: Primary oscillator w/ PLL
#pragma config FPLLMUL = MUL_20     // PLL Multiplier: Multiply by 20
#pragma config FPLLIDIV = DIV_2     // PLL Input Divider:  Divide by 2
#pragma config FPLLODIV = DIV_1     // PLL Output Divider: Divide by 1
#pragma config FPBDIV = DIV_1       // Peripheral Bus Clock: Divide by 1
#pragma config UPLLEN = ON          // USB clock uses PLL
#pragma config UPLLIDIV = DIV_2     // Divide 8 MHz input by 2, mult by 12 for 48 MHz
#pragma config FUSBIDIO = ON        // USBID controlled by USB peripheral when it is on
#pragma config FVBUSONIO = ON       // VBUSON controlled by USB peripheral when it is on
#pragma config FSOSCEN = OFF        // Disable second osc to get pins back
#pragma config BWP = ON             // Boot flash write protect: ON
#pragma config ICESEL = ICS_PGx2    // ICE pins configured on PGx2
#pragma config FCANIO = OFF         // Use alternate CAN pins
#pragma config FMIIEN = OFF         // Use RMII (not MII) for ethernet
#pragma config FSRSSEL = PRIORITY_6 // Shadow Register Set for interrupt priority 6

#define NU32_DESIRED_BAUD 9600 //115200 //230400    // Baudrate for RS232

#define NU32_DESIRED_BAUD_UART2 9600 //115200    // Baudrate for RS232

// Perform startup routines:
//  Make NU32_LED1 and NU32_LED2 pins outputs (NU32_USER is by default an input)
//  Initialize the serial port - UART3 (no interrupt) 
//  Enable interrupts
void NU32_Startup() {
  // disable interrupts
  __builtin_disable_interrupts();

  // enable the cache 
  // This command sets the CP0 CONFIG register
  // the lower 4 bits can be either 0b0011 (0x3) or 0b0010 (0x2)
  // to indicate that kseg0 is cacheable (0x3) or uncacheable (0x2)
  // see Chapter 2 "CPU for Devices with M4K Core" of the PIC32 reference manual
  // most of the other bits have prescribed values
  // microchip does not provide a _CP0_SET_CONFIG macro, so we directly use
  // the compiler built-in command _mtc0
  // to disable cache, use 0xa4210582 
  __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583); 
  
  // set the prefectch cache wait state to 2, as per the
  // electrical characteristics data sheet
  CHECONbits.PFMWS = 0x2;   

  //enable prefetch for cacheable and noncacheable memory
  CHECONbits.PREFEN = 0x3; 

  // 0 data RAM access wait states
  BMXCONbits.BMXWSDRM = 0x0;
  
  // enable multi vector interrupts
  INTCONbits.MVEC = 0x1;

  // disable JTAG to get B10, B11, B12 and B13 back
  DDPCONbits.JTAGEN = 0;

  TRISFCLR = 0x0003;  // Make F0 and F1 outputs (LED1 and LED2)
  NU32_LED1 = 1;      // LED1 is off
  NU32_LED2 = 0;      // LED2 is on

  // turn on UART3 without an interrupt
  U3MODEbits.BRGH = 0; // set baud to NU32_DESIRED_BAUD
  U3BRG = ((NU32_SYS_FREQ / NU32_DESIRED_BAUD) / 16) - 1;

  // 8 bit, no parity bit, and 1 stop bit (8N1 setup)
  U3MODEbits.PDSEL = 0;
  U3MODEbits.STSEL = 0;

  // configure TX & RX pins as output & input pins
  U3STAbits.UTXEN = 1;
  U3STAbits.URXEN = 1;
  // configure hardware flow control using RTS and CTS
  U3MODEbits.UEN = 2;//0;//2;

  // enable the uart
  U3MODEbits.ON = 1;

  // turn on UART3 without an interrupt
  U2MODEbits.BRGH = 0; // set baud to NU32_DESIRED_BAUD
  U2BRG = ((NU32_SYS_FREQ / NU32_DESIRED_BAUD_UART2) / 16) - 1;

  // 8 bit, no parity bit, and 1 stop bit (8N1 setup)
  U2MODEbits.PDSEL = 0;
  U2MODEbits.STSEL = 0;

  // configure TX & RX pins as output & input pins
  U2STAbits.UTXEN = 1;
  U2STAbits.URXEN = 1;
  // configure hardware flow control using RTS and CTS
  U2MODEbits.UEN = 0;//2;//0; 0 = disabled, 2 = enabled

  U2STAbits.URXISEL = 0x0; // interrupt when buffer not empty

  // enable the uart
  U2MODEbits.ON = 1;

  __builtin_enable_interrupts();
}

// Read from UART3
// block other functions until you get a '\r' or '\n'
// send the pointer to your char array and the number of elements in the array
void NU32_ReadUART3(char * message, int maxLength) {
  char data = 0;
  uint32_t complete = 0, num_bytes = 0;
  // loop until you get a '\r' or '\n'
  while (!complete) {
    if (U3STAbits.URXDA) { // if data is available
      data = U3RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= 2){ //maxLength) {
          complete = 1;
          //num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';
}

// Write a character array using UART3
void NU32_WriteUART3(const char * string) {
  while (*string != '\0') {
    while (U3STAbits.UTXBF) {
      ; // wait until tx buffer isn't full
    }
    U3TXREG = *string;
    ++string;
  }
}

// Write a character array using UART2
void NU32_WriteUART2(const char * string) {
  while (*string != '\0') {
    while (U2STAbits.UTXBF) {
      ; // wait until tx buffer isn't full
    }
    U2TXREG = *string;
    ++string;
  }
}

void NU32_ReadUART2(char * message, int maxLength) {
  char data = 0;
  uint32_t complete = 0, num_bytes = 0;
  // loop until you get a '\r' or '\n'
  while (!complete) {
    if (U2STAbits.URXDA) { // if data is available
      data = U2RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';
}

/*void NU32_ReadUART2(char * message, int maxLength) {
  char data = 0;
  uint32_t complete = 0, num_bytes = 0, c = 0;
  // loop until you get a '\r' or '\n'
  while (!complete && (c < 10000) && (num_bytes <= maxLength)) { //&& c < 1000000) {
    c++;
    NU32_WriteUART3("abc\r\n");
    if (U2STAbits.URXDA) { // if data is available
      data = U2RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          num_bytes = 0;
        }
      }
    }*/
    /*if (c >= 1000) {
      message[num_bytes] = '\0';
      //NU32_WriteUART3(message);
      //NU32_WriteUART3("********************************abc\r\n");
      c = 0;
      //if (U2STAbits.OERR) {
      U2STAbits.OERR = 0;
      U2STAbits.FERR = 0;
      U2STAbits.PERR = 0;
      //}
      complete = 1;
      break;
    }*/
//   }
//   // end the string
//   message[num_bytes] = '\0';
// }

void writeLineUART3(const char * string) {
  NU32_WriteUART3(string);
  NU32_WriteUART3("\r\n");  
}

void writeLineUART2(const char * string) {
  NU32_WriteUART2(string);
  NU32_WriteUART2("\r\n");
}

/*void NU32_ReadUART2Original(char * message, int maxLength) {
  char data = 0;
  uint32_t complete = 0, num_bytes = 0;
  // loop until you get a '\r' or '\n'
  while (!complete) {
    if (U2STAbits.URXDA) { // if data is available
      data = U2RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';
}

void ShortNU32_ReadUART2Original(char * message, int maxLength) {
  char data = 0;
  uint32_t complete = 0, num_bytes = 0;
  // loop until you get a '\r' or '\n'
  while (!complete) {
    if (U2STAbits.URXDA) { // if data is available
      data = U2RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          NU32_WriteUART3("inside: ");
          NU32_WriteUART3(data);
          NU32_WriteUART3("\r\n");
          num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';
}*/

// Read from UART2
// DO NOT block other functions until you get a '\r' or '\n'
// send the pointer to your char array and the number of elements in the array
/*void NU32_ReadUART2(char * message, int maxLength) {
  char data = 0;
  uint32_t complete = 0, num_bytes = 0;
  uint32_t timer = 0, timer0 = 0;
  char snum[20];
  char d[20];
  // loop until you get a '\r' or '\n'
  while(timer0 < 20000000) {
    if (U2STAbits.URXDA) { // if data is available
      while (timer < 80000000 && !complete) {
        //if (U2STAbits.URXDA) { // if data is available ////////////////////////////
        data = U2RXREG;      // read the data
        if ((data == '\n') || (data == '\r')) {
          complete = 1;
        } else {
            //num_bytes = 0;
            complete = 1;
            num_bytes = 0;
          }
        }
        message[num_bytes] = data;
        //sprintf(d, "datahex: %x\r\n", data);
        //NU32_WriteUART3(d);
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          //num_bytes = 0; ////////////// If this is here, the first byte gets set to the null terminator....at least when the loop is done, that is
          complete = 1;
        }
        //}
        timer++;
      }
    }
    timer0++;
  }
  // end the string
  message[num_bytes] = '\0';
  //NU32_WriteUART3(message);
  //NU32_WriteUART3("\r\nJust Printed message from uart2\r\n");
}
/*
void NU32_ReadUART2Wait(char * message, int maxLength) {
  char data = 0;
  uint32_t complete = 0, num_bytes = 0;
  // loop until you get a '\r' or '\n'
  while (!complete) {
    if (U2STAbits.URXDA) { // if data is available
      data = U2RXREG;      // read the data
      if ((data == '\n') || (data == '\r')) {
        complete = 1;
      } else {
        message[num_bytes] = data;
        ++num_bytes;
        // roll over if the array is too small
        if (num_bytes >= maxLength) {
          num_bytes = 0;
        }
      }
    }
  }
  // end the string
  message[num_bytes] = '\0';
}*/