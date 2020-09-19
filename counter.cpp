#include "counter.hpp"
#include <iostream>
GeigerCounter::GeigerCounter() : port()
{
}

void GeigerCounter::turnOn(){
    port.sendCommand("POWERON");
}

void GeigerCounter::turnOff(){
    port.sendCommand("POWEROFF");
}

void GeigerCounter::reboot(){
    port.sendCommand("REBOOT");
}