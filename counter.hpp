#include "serial.hpp"

class GeigerCounter{
    private:
        SerialPort port;
        float voltage;
        unsigned int cpm, cps, cpm_hi, cpm_lo;

    public:
        GeigerCounter();
        void turnOn();
        void turnOff();
        void reboot();
        void readCPM();
        void readCPM_HI();
        void readCPM_LO();
        void readCPS();
        void readVoltage();
        unsigned int getCPM();
        unsigned int getCPM_LO();
        unsigned int getCPM_HI();
        unsigned int getCPS();
        float getVoltage();

    private:
        unsigned int convertReadBytes(unsigned char* buf_ptr);
};