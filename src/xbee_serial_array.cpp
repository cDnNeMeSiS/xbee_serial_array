#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <Arduino.h> 
#include "HardwareSerial.h"
#include "SoftwareSerial.h"
#include <xbee_serial_array.h>

SoftwareSerial xbee_Serial(5, 4);

void xbee::xbee_in_array() {
	if (xbee_Serial.available()>0) {
		bufferin[count] = xbee_Serial.read()&0xFF;
		if (count>2) {
			if ((bufferin[count-3]==0x7E)&&!bandera){
				bandera = true;
				largo = bufferin[count - 1];
				lai = count - 3;
				dataini = lai + 3;
				datafin = lai + 2 + largo;	
			}
		}
		if ((checksum(dataini, datafin,'I') == (bufferin[count] & 0xFF))&&(count>(largo+2))) {
			end_byte = count;
			entry = true;
			count = 0;
			bandera = false;
		}
		else {
			count++;
		}
	}
}

bool xbee::xbee_detected() {
	if (entry) {
		entry = false;
		return true;
	}
	else {
		return false;
	}
}

int xbee::endbyte_pos() {
	return end_byte;
}

char xbee::buffer(int posi) {
	return bufferin[posi];
}

String xbee::array_concat(int ini, int fin) {
	String concat;
	for (size_t i = ini; i <= fin; i++) concat += bufferin[i]&0xFF;
	return concat;
}

String xbee::getdata() {
	String data;
	if (largo==0x07) {
		for (size_t i = dataini; i <= datafin; i++) {
			data += bufferin[i];
			//bufferin[i] = ' ';
		}
	}
	else {
		for (size_t i = dataini + 18; i <= datafin; i++) {
			data += bufferin[i];
			//bufferin[i] = ' ';
		}
	}
	memset(bufferin, 0, sizeof(bufferin));
	return data;
}

void xbee::begin(int speed, char buffer[],int pin) {
	pinMode(pin, OUTPUT);
	wakeperro = pin;
	digitalWrite(wakeperro, LOW);
	xbee_Serial.begin(speed);
	for (size_t i = 0; i < 8; i++) bufferout[i+5] = buffer[i];
}

uint8_t xbee::checksum(int ini, uint8_t fin, char bufa) {
	int suma = 0;	
	if (bufa == 'I')	for (int r = ini; r <= fin; r++) suma += bufferin[r] & 0x0FF; //xbeeFrame is the array where are stored the bytes' frame
	if (bufa == 'O')	for (int r = ini; r <= fin; r++) suma += bufferout[r] & 0x0FF; 
	return (0xFF - suma);
}

void xbee::sendata(String data) {
	char buff[100];
	bufferout[0] = 0x7E; bufferout[1] = 0x00;
	bufferout[2] = data.length()+14;
	bufferout[3] = 0x10; bufferout[4] = 0x01;
	bufferout[13] = 0xFF; bufferout[14] = 0xFE;
	bufferout[15] = 0x00; bufferout[16] = 0x00;
	
	data.toCharArray(buff,data.length()+1);
	
	int i = 17;
	while (data.length()+17>i){
		bufferout[i] = buff[i - 17];
		i++;
	}
	bufferout[data.length()+17]=checksum(3, data.length() + 16, 'O');
	digitalWrite(wakeperro, HIGH);
	delay(10);
	digitalWrite(wakeperro, LOW);
	delay(10);
	for (size_t i = 0; i < data.length() + 18; i++) xbee_Serial.write(bufferout[i] & 0xFF);
	memset(buff, 0, sizeof(buff));
	memset(bufferout, 0, sizeof(bufferout));
}
