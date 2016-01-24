import serial

port = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout = 10.0)

while (1):
	rcv = port.read(1)
	print("Received: ",  rcv)
	port.write(rcv)

print("Done!")
