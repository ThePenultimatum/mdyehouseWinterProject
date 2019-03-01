#include <stdint.h>
#include "myNU32.h"

/*
Using UART2, send an AT request for a property to the xbee
*/
void getXBeePropertyAT(char * string, const char * propertyAT);