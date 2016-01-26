import serial

port = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout = 3.0)

msg = "Hello Raspberry Pi!"

for char in msg:
	port.write(bytes(char, "ASCII"))
	rcv = port.read(1)
	print("Received: ",  rcv.decode("utf-8"))

print("Done!")
