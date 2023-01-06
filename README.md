# BLE-CBCP
Proof of concept for command based connection parameters (CBCP).
Similar to modem connections using `AT` commands to configure a device.
The intent here is to have the user give the BLE device simple commands
to set parameters, send and receive data etc.
This eliminates the need to use the MSDK at all. Aside from initial flashing of the device.

The user would simply have a device preprogrammed, or flash it themselves,  with this CBCP applciation
and connect it to the PC via USB for a UART prompt. The UART prompt is used to configure the device
as needed per their application.
The device then stores the configurations in NVM for future use.

The BLE device is NOT the home of the users main application, infact the BLE device is 
simply a peripheral to some other microcontroller. The interface between the two being is the
UART prompt. 

User can pre configure the BLE device or have the main microcontroller configure it on the fly.

This means two device using the CBCP application act basically as UART devices 
communicating wirelessly, and that is the goal.
A simple interface to send data back and forth with no intimate Bluetooth programing knowledge.

Is this wasteful, using a fully blown MCU with 2 cores as a simple Bluetooth UART? Absolutely.
However more features can be added, like have the BLE device make use of its own onboard peripherals
and send that data wirelessly. Similar to these cheap Bluetooth RX/TX modules, but with more planned functionality.
So it may be wasteful but some people just want to send a byte or two and thats why the modules show below sell like hotcakes.


![image](https://user-images.githubusercontent.com/62710807/211102374-3848f2a3-1bb3-487b-b2ae-0c52b50c4917.png)


### Planned features
- Abillity to TX/RX small chucnks of data with optional ACK/NACK
- Secuirity enable features
- File transfer mechanism for larger data streams.
- Send sleep commands to put peer device to sleep


