#include "serial.hpp"
#include <iostream>
#include <unistd.h>

int main(void){
	SerialPort s1;
    while(1){
    s1.sendCommand("GETCPMH");
    usleep(100000);
    s1.receiveData();}
    return 0;
}
