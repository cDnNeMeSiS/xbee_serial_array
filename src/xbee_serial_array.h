#ifndef XBEE_SERIAL_ARRAY_H
#define XBEE_SERIAL_ARRAY_H

class xbee {
public:
	void xbee_in_array();
	int endbyte_pos();
	bool xbee_detected();
	String array_concat(int ini, int fin);
	char buffer(int posi);
	void begin(int speed, char buffer[], int pin);
	String getdata();
	uint8_t checksum(int ini, uint8_t fin, char bufa);
	void sendata(String data);

private:
	int wakeperro;
	char bufferin[100];
	char bufferout[100];
	size_t count=0;
	size_t end_byte=0;
	bool entry;
	bool bandera;
	size_t largo;
	size_t lai;
	int dataini;
	int datafin;
};

#endif // !XBEE_API_H