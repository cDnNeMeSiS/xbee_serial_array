# xbee_array_arduino
send and receive strings in api mode with variable length of data
version:  v.9
creator: cDn_NeMeSiS

by now, the idea is works in api mode and software serial in the easiest way
to get working with parameters of sofware serial is mandatory modify the software serial library, but 
in this moment the config of the pins for software serial is in the cpp file of this library
in the examples show how config in order to get working the system

methods

keeps detecting data on software serial to fill an array input
void xbee::xbee_in_array() 

when a valid frame is detected puts a flag true to process the data
bool xbee::xbee_detected() 

return the position of the ending byte
int xbee::endbyte_pos() 

return the byte in buffer position
char xbee::buffer(int posi)

return a concatenated string between a initial an ending position
String xbee::array_concat(int ini, int fin) 

return the data in frame array from xbee
String xbee::getdata()

configure speed of software serial, mac for the xbee coordinator, pin for wake up xbee
void xbee::begin(int speed, char buffer[],int pin)

calculate the checksumbyte depens if is input frame or output frame
uint8_t xbee::checksum(int ini, uint8_t fin, char bufa) 

send a string data from xbee to coordinator
void xbee::sendata(String data) 
