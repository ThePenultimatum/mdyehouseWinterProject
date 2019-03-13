#include "xbeeInterfacing.h"

#define MAX_PROP_LEN 100

/*
Using UART2, send an AT request for a property to the xbee
*/
void getXBeePropertyAT(char * string, const char * propertyAT) {
  uint32_t j = 0;
  NU32_WriteUART2("+++");
  while (j < 80000000) {
  	j++;
  	Nop();
  }
  j = 0;
  NU32_WriteUART2(propertyAT);
  while (j < 80000000) {
  	j++;
  	Nop();
  }  
  NU32_ReadUART2(string, MAX_PROP_LEN);
}