#include "rs232.h"
#include "serial.hpp"
#include <iostream>
#include <string>

SerialPort::SerialPort(){
    setPortNumber(16); //Default port corresponds to /dev/USB0
    setBaudRate(115200); //That's the default baud rate of the geiger counter
    setMode("8N1");
}

SerialPort::SerialPort(int p_n, int bd_rate, std::string md){
    setPortNumber(p_n);
    setBaudRate(bd_rate);
    setMode(md);
}

void SerialPort::openPort(){
    if(!RS232_OpenComport(port_num, baud_rate, mode.c_str(), 0)) std::cout<< "OPEN" << std::endl; //I know cout here is bad practice but I am using it so far just for the debugging reason. I'll delete it later.
    else std::cout << "NOPE" << std::endl;
}

void SerialPort::setPortNumber(int p_n) {port_num = p_n;}
void SerialPort::setBaudRate(int bd_rate) {baud_rate = bd_rate;}
void SerialPort::setMode(const char* md) {mode = md;}
void SerialPort::setMode(std::string md) {mode = md.c_str();}
int SerialPort::getPortNumber() {return port_num;}
int SerialPort::getBaudRate() {return baud_rate;}
std::string SerialPort::getMode() {return mode;}
