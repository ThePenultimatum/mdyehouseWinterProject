# mdyehouseWinterProject

This project attempts to use HC-SR04 ultrasonic sensors in conjunction with NU32 boards using PIC32 microcontrollers and XBee radio tranceivers in a sensor network for localization of a mobile robot. The goal is to allow the mobile robot to navigate a simple space in limited sensor circumstances.

The ultrasonic sensors are hooked up and receive a >=5 millisecond pulse of 5V from the PIC32, and then the returned signal is timed for a time of flight distance measurement. This is done by all nodes in the network, and they transmit their measurements in AT mode to a central node. This central node aggregates and processes the distances for trilateration of an object in the network's measurement area. This object can be a mobile robot enabled with an XBee RF module which receives a measure which it can then minimize toward a known goal location within the network.

Resources:
XBee Data sheet: https://www.sparkfun.com/datasheets/Wireless/Zigbee/XBee-Datasheet.pdf
Notes on trilateration: https://math.stackexchange.com/questions/884807/find-x-location-using-3-known-x-y-location-using-trilateration

Trilateration summary:

(-2* x1 + 2 * x2) * x + (-2 * y1 + 2 * y2) * y = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2
(-2* x2 + 2 * x3) * x + (-2 * y2 + 2 * y3) * y = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2

=>

Ax + By = C
Dx + Ey = F

x = (CE - FB)/(EA - BD)
y = (CD - AF)/(BD - AE)
