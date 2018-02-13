# Dominus App

## Main Server

This is the binary of the main server for Dominus.  
It starts a TCP server that listens for upcoming messages and changes the GPIO status accordingly.  
The arguments passed are:
* port: the port of the TCP server
* pin: the GPIO pin number

Example (default configuration):

		./main_server 29200 18


## Main Client

This is the binary of the main client for the communication between Domoticz and Dominus.  
It starts a TCP client that sends a command to the Dominus server to set the value of the GPIO pin.  
The arguments passed are:
* ip: the ip address of the host of the Dominus server
* port: the port of the TCP
* value: the value assigned to the pin (must be 0 or 1)

Example (default configuration):

		./main_client 127.0.0.1 29200 1
