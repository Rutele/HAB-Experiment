#include "rs232.h"
#include "serial.hpp"
#include <iostream>
#include <string>

#define buffer_size 4096

SerialPort::SerialPort(){
    //This method opens the default port at which the meter is connected. This constructor is preffered
    setPortNumber(16); //Default port corresponds to /dev/USB0
    setBaudRate(115200); //That's the default baud rate of the geiger counter
    setMode("8N1");
    openPort();
}

SerialPort::SerialPort(int p_n, int bd_rate, std::string md){
    //Use this constructor if for any other reason defaults don't work
    setPortNumber(p_n);
    setBaudRate(bd_rate);
    setMode(md);
    openPort();
}

SerialPort::~SerialPort(){
    RS232_CloseComport(port_num);
}

void SerialPort::openPort(){
    RS232_OpenComport(port_num, baud_rate, mode.c_str(), 0);
}

void SerialPort::sendCommand(std::string cmd){
    correctMessage(cmd);
    RS232_cputs(port_num, (cmd+'\0').data()); //String needs to be null-terminated
}

void SerialPort::correctMessage(std::string &msg){
    //I am not sure wether that's a tottaly good idea but I don't really want to play with copying str on RPi
    msg.insert(0, "<");
    msg.append(">>");
}

int SerialPort::receiveData(){
    int n = RS232_PollComport(port_num, buf, buffer_size-1);
    if (n>0){
        buf[n] = 0; //terminate the buffer
    }
    printf("received %i bytes: %s\n", n, (char *)buf); // FOR DEBUG
    return n; //It returnes the numbers of bytes received
}

void SerialPort::setPortNumber(int p_n) {port_num = p_n;}
void SerialPort::setBaudRate(int bd_rate) {baud_rate = bd_rate;}
void SerialPort::setMode(const char* md) {mode = md;}
void SerialPort::setMode(std::string md) {mode = md.c_str();}
int SerialPort::getPortNumber() {return port_num;}
int SerialPort::getBaudRate() {return baud_rate;}
std::string SerialPort::getMode() {return mode;}
