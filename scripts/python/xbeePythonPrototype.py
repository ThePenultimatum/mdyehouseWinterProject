from digi.xbee.devices import Raw802Device

port0 = "/dev/ttyUSB0"
port1 = "/dev/ttyUSB1"
br = 115200
dataToSend = "abc"
d0 = Raw802Device(port0, br)
d0.open()
d1 = Raw802Device(port1, br)
d1.open()

