# Sensor Network for Mobile Robot Localization
**Mark Dyehouse**

*Northwestern University*

## Introduction

This project aims to use HC-SR04 ultrasonic sensors in conjunction with NU32 boards using PIC32 microcontrollers and XBee radio tranceivers in a sensor network for localization of a mobile robot. The goal is to allow the mobile robot to navigate a simple space in limited sensor circumstances.

The ultrasonic sensors are hooked up and receive a >=5 millisecond pulse of 5V from the PIC32, and then the returned signal is timed for a time of flight distance measurement. This is done by all nodes in the network, and they transmit their measurements in AT mode to a central node. This central node aggregates and processes the distances for trilateration of an object in the network's measurement area. This object can be a mobile robot enabled with an XBee RF module which receives a measure which it can then minimize toward a known goal location within the network. Instead of using UART3 to send data to a computer, this would require sending data back over UART2 to the XBee radio tranceiver directly to the XBee on the mobile robot.

## Background

### Requirements

* 4+ NU32 boards with PIC32 microcontrollers (1 per node including central node)
* 3+ HC-SR04 ultrasonic sensors (1 per node)
* 4+ XBee units (one per node including central node)
    - Along with this, it is helpful to have a breakout board with header pins for each XBee
* Wire for connecting components (and wire-strippers)
* Soldering equipment
* 4+ breadboards or something with which to connect components

### HC-SR04 Measurements:

Vertical angle range (measurements taken at about 1 meter distance from the sensor with surface perpendicular to ultrasonic signal):
1 degree below plane of measurement
6.0 degrees above plane of measurement

Horizontal angle range (measurements taken at about 1 meter distance from the sensor with surface perpendicular to ultrasonic signal)
14.5 degrees with 1-2 degrees of variation from side to side

These range measurements are most accurate with orthogonal surfaces and decrease as the angle of the surface to the signal moves away from 90 degrees. However, a range of about 5-10 degrees remains accurate regardless of surface in front of the sensor.

Due to the angular range limitations on these sensors, the ideal setup includes angling multiple sensors in conjunction and fusing the data from them.

### Trilateration summary:

Trilateration is related to triangulation but different in that it does not use angles. Instead, it uses distances. These can be thought of as radii of circles around three initial, known points. These are our edge nodes in this project. This architecture can be repeated in many different adjacent or overlapping triangles. Since we have three circles and three distances, we can find the intersection between the three. It is important to consider that there may not be three good measurements, and this will bring to the forefront a flow of measurement possibilities. For now, we will only look at having three good measurements. The known positions are of the nodes at locations (x_i, y_i) for each node with index i.

(-2* x1 + 2 * x2) * x + (-2 * y1 + 2 * y2) * y = (r1)^2 - (r2)^2 - (x1)^2 + (x2)^2 - (y1)^2 + (y2)^2
(-2* x2 + 2 * x3) * x + (-2 * y2 + 2 * y3) * y = (r2)^2 - (r3)^2 - (x2)^2 + (x3)^2 - (y2)^2 + (y3)^2

=>

Ax + By = C
Dx + Ey = F

x = (CE - FB)/(EA - BD)
y = (CD - AF)/(BD - AE)

## Implementation

### Sensor Signals

In order to acheive a distance measurement using the HC-SR04 ultrasonic sensors, the sensor must be powered with 5V to VCC, grounded, and receive a high signal pulse for greater than 5 milliseconds. This signal is sent to the trig pin (short for "trigger") to initialize the sensor's sending of the ultrasonic pulses. The result is a signal received on the echo pin. The signal is high for the period of time during which a return signal has not been received by the HC-SR04. This 



## File Structure

### endNode

This contains endNode.c which is the code that runs on edge nodes which send data to the central node.

### centralNode

This contains centralNode.c which is the central aggregator and processor of distance information for a group of 3 nodes.

### images

The contents of this directory are diagrams and images of the individual nodes themselves during the development process.

### libxbee3

This is an API library for use with the XBee units which will be more heavily leveraged during the transition to using API mode instead of AT mode but which is not currently used.

### scripts

This contains a Python prototype for testing connectivity between XBee units on development boards.

### xbee_ansic_library

This is currently not used but will be more heavily leveraged during the transition into using API mode instead of AT mode.

### docs

This directory contains assorted documents related to the initial development of this project.

### Resources:

* XBee Data sheet: https://www.sparkfun.com/datasheets/Wireless/Zigbee/XBee-Datasheet.pdf
* Notes on trilateration: https://math.stackexchange.com/questions/884807/find-x-location-using-3-known-x-y-location-using-trilateration

## Contributing

If contributing to the modifications in our project here, please follow the following steps:
* Fork the repository
* Add your modifications to either the dev branch or a branch off of the dev branch
* Make a pull request with informative descriptions

## Author

* **Mark Dyehouse** - *Initial work* - [ThePenultimatum](https://github.com/ThePenultimatum)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Matt Elwin at Northwestern University
* Nick Marchuk at Northwestern University