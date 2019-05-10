# xbee_array_arduino
### Send and receive strings in api mode with variable length of data
### Version:  v1.0.5
### Creator: cDn_NeMeSiS

by now, the idea is works in api mode and software serial in the easiest way.

to get working with parameters of sofware serial is mandatory modify the software serial library, 

but in this moment the config of the pins for software serial is in the cpp file of this library

in the example show how config in order to get working the system

# methods

#### keeps detecting data on software serial to fill an array input
``` c++
void xbee::xbee_in_array() 
```

#### when a valid frame is detected puts a flag true to process the data
``` c++
bool xbee::xbee_detected() 
```
#### return the position of the ending byte
``` c++ 
int xbee::endbyte_pos() 
```

#### return the byte in buffer position
``` c++
char xbee::buffer(int posi)
```

#### return a concatenated string between a initial an ending position
``` c++
String xbee::array_concat(int ini, int fin) 
```

#### return the data in frame array from xbee
``` c++
String xbee::getdata()
```

#### configure speed of software serial, mac for the xbee coordinator, pin for wake up xbee
``` c++
void xbee::begin(int speed, char buffer[],int pin)
```

#### calculate the checksumbyte depens if is input frame or output frame
``` c++
uint8_t xbee::checksum(int ini, uint8_t fin, char bufa) 
```

#### send a string data from xbee to coordinator
``` c++
void xbee::sendata(String data) 
```

# Example to receive data and send analog data string on xbee

``` c++
/*
in xbee_serial_array.cpp must change software serial pins
*/
#include <xbee_serial_array.h>

uint8_t wakeup = 9;
xbee xbeeSerial;
char xbeedir[8] = {0x00, 0x13, 0xA2, 0x00, 0x40, 0xE6, 0x71, 0x55};//coordinator
String anal;
String response;

// the setup function runs once when you press reset or power the board
void setup() {
	xbeeSerial.begin(9600, xbeedir, wakeup);
	Serial.println("online");
}

// the loop function runs over and over again until power down or reset
void loop() {
	xbeeSerial.xbee_in_array();//siempre recive datos
	if (xbeeSerial.xbee_detected()) {
		response = xbeeSerial.getdata();
		Serial.println(response);
		if (response == "anal") {
			Serial.println("Recibido");
			anal = String(analogRead(luz));
			xbeeSerial.sendata(anal);
		}
	}
}
```
