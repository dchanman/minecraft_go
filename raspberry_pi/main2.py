import serial
import time
from mcpi.minecraft import Minecraft
import rainbow
#from mock import Minecraft

#######################################
# Initialize ports 
#######################################
mc = Minecraft.create()
port = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout = 3.0)
rainbow.rainbow_delete(mc)
mc.postToChat("Minecraft GO Server Connected")

#######################################
# main_loop
#######################################
def main_loop():
	rcv = port.read(1)
	
	if rcv == b'#':
		rcv = port.read(2)
		if rcv in function_map:
			print("Handling " + rcv.decode("utf-8"))
			function_map[rcv](b'#'+ rcv)
			print()
		else:
			print("Received unknown command: ", rcv)


def _send_and_check(byte, length):
	port.write(byte)
	rcv = port.read(length)
	if (rcv != byte):
		print("_send_and_check: expected <" + byte.decode("utf-8") + "> got <" + rcv.decode("utf-8") + ">")
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
	
	###################################
	# Protocol Steps
	###################################
	
	# Echo #rc
	port.write(rpc_code)
	
	# Send lat_minute
	lat_minute = "15.7101".encode('utf-8')
	if not _send_and_check(lat_minute, 7):
		print("Error sending lat_minute")

	# Send lat_degree
	lat_degree = "49".encode('utf-8')
	if not _send_and_check(lat_degree, 2):
		print("Error sending lat_degree")

	# Send lat_direction
	lat_direction = "N".encode('utf-8')
	if not _send_and_check(lat_direction, 1):
		print("Error sending lat_direction")

	# Send long_minute
	long_minute = "14.9949".encode('utf-8')
	if not _send_and_check(long_minute, 7):
		print("Error sending long_minute")

	# Send long_degree
	long_degree = "123".encode('utf-8')
	if not _send_and_check(long_degree, 3):
		print("Error sending long_degree")

	# Send long_direction
	long_direction = "W".encode('utf-8')
	if not _send_and_check(long_direction, 1):
		print("Error sending long_direction")
	
	# Wait for #rc
	rcv = port.read(3)
	if (rcv != rpc_code):
		print("Error closing connection")
		
	# Send #rc
	port.write(rpc_code)
	
	###################################
	# Processing Steps
	###################################
	mc.postToChat("New GPS coordinates uploaded!")
	print("New GPS coordinates uploaded")
	mc.postToChat("")
	mc.postToChat("Destination:")
	mc.postToChat("Fred Kaiser Building")
	
#######################################
# rpc_journey_complete
#
# Receive journey complete information
#######################################
def rpc_journey_complete(rpc_code):
	mc.postToChat("Receiving journey statistics...")
	
	###################################
	# Protocol Steps
	###################################
	
	# Echo #jc
	port.write(rpc_code)
	
	# Receive elapsed time
	elapsed_time = _receive_and_echo(9)
	
	# Receive creeps encountered
	creep_encounters = _receive_and_echo(3)
	
	# Wait for #jc
	rcv = port.read(3)
	if (rcv != rpc_code):
		print("Error closing connection")
		
	# Send #jc
	port.write(rpc_code)
	
	###################################
	# Processing Steps
	###################################
	time_vals = str(elapsed_time.decode("utf-8")).split(":")
	hours = int(time_vals[0])
	minutes = int(time_vals[1])
	seconds = int(time_vals[2])
	
	creeps = int(creep_encounters.decode("utf-8"))
		
	mc.postToChat("Journey Statistics:")
	mc.postToChat("Elapsed Time: {0}h {1}m {2}s".format(hours, minutes, seconds))
	mc.postToChat("Creeps Defeated: {0}".format(creeps))
	rainbow.rainbow_make(mc)
	print("Journey Stats: Elapsed Time {0}h {1}m {2}s | Creeps {3}".format(hours, minutes, seconds, creeps))


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
