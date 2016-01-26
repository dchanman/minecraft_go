import serial
import time
from mcpi.minecraft import Minecraft


#######################################
# Initialize ports 
#######################################
mc = Minecraft.create()
port = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout = 10.0)


#######################################
# main_loop
#######################################
def main_loop():
	rcv = port.read(1)
	
	if rcv == b'#':
		rcv = port.read(2)
		if rcv in function_map:
			function_map[rcv]()
		else:
			print("Received unknown command: ", rcv)


#######################################
# rpc_hi
#
# Simple hello message 
#######################################
def rpc_hi():
	mc.postToChat("Minecraft GO Connected!")


#######################################
# This function map uses received 
# messages from the rs232 as keys and
# functions as values. 
#######################################
function_map = {
	b'hi': rpc_hi
}



#######################################
# Program execution starts here 
#######################################
while (True):
	main_loop()
