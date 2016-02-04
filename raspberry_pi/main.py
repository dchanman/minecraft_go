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
			function_map[rcv](rcv)
		else:
			print("Received unknown command: ", rcv)


def _send_and_check(byte, length):
	port.write(byte)
	rcv = port.read(length)
	if (rcv != byte):
		return False
	else:
		return True
		
def _receive_and_echo(length):
	rcv = port.read(length)
	port.write(rcv)
	return rcv

#######################################
# rpc_hi
#
# Simple hello message 
#######################################
def rpc_hi(rpc_code):
	mc.postToChat("Minecraft GO Connected!")
	# Echo #hi
	port.write(rpc_code)
	
#######################################
# rpc_recv_coordinates
#
# Send new GPS destination coordinates
#######################################
def rpc_recv_coordinates(rpc_code):
	mc.postToChat("Sending new GPS coordinates...")
	# Echo #rc
	port.write(rpc_code)
	
	# Send latitude[9]
	new_latitude = byte("ddmm.mmmm")
	if not _send_and_check(new_latitude):
		print("Error sending new_latitude")
	
	# Send longitude[10]
	new_longitude = byte("dddmm.mmmm")
	if not _send_and_check(new_longitude):
		print("Error sending new_longitude")
	
	# Wait for #rc
	rcv = port.read(2)
	if (rcv != rpc_code):
		print("Error closing connection")
		
	# Send #rc
	port.write(rpc_code)
	
	mc.postToChat("New GPS coordinates uploaded!")
	
#######################################
# rpc_journey_complete
#
# Receive journey complete information
#######################################
def rpc_journey_complete(rpc_code):
	mc.postToChat("Receiving journey statistics...")
	# Echo #jc
	port.write(rpc_code)
	
	# Receive elapsed time
	elapsed_time = _receive_and_echo(9)
	print("elapsed_time: " + str(elapsed_time))
	
	# Receive creeps encountered
	creep_encounters = _receive_and_echo(3)
	print("creep_encounters: " + str(creep_encounters))
	
	# Wait for #jc
	rcv = port.read(2)
	if (rcv != rpc_code):
		print("Error closing connection")
		
	# Send #jc
	port.write(rpc_code)
	
	mc.postToChat("Journey Statistics:")
	mc.postToChat("Elapsed Time: " + str(elapsed_time))
	mc.postToChat("Creeps Encountered: " + str(creep_encounters))


#######################################
# This function map uses received 
# messages from the rs232 as keys and
# functions as values. 
#######################################
function_map = {
	b'hi': rpc_hi,
	b'rc': rpc_recv_coordinates,
	b'jc': rpc_journey_complete
}



#######################################
# Program execution starts here 
#######################################
while (True):
	main_loop()
