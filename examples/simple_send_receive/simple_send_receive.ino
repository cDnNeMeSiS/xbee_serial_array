#include <xbee_serial_array.h>

uint8_t wakeup = 9;
xbee xbeeSerial;
char xbeedir[8] = {0x00, 0x13, 0xA2, 0x00, 0x40, 0xE6, 0x71, 0x55};
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
