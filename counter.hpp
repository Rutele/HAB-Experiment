#include "serial.hpp"

class GeigerCounter{
    private:
        SerialPort port;
    public:
        GeigerCounter();
        void turnOn();
        void turnOff();
        void reboot();
};