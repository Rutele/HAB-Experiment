#include "serial.hpp"
#include <iostream>

int main(void){
	SerialPort s1;
    std::cout << s1.getPortNumber() << std::endl;
    s1.openPort();
    return 0;
}
