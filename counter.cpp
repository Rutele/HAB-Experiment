#include "counter.hpp"
#include <unistd.h>

#define WAIT_TIME 100000

GeigerCounter::GeigerCounter() : port(), voltage(-1.), cpm(0), cps(0), cpm_hi(0), cpm_lo(0)
{
    readVoltage();
    readCPM();
    readCPS();
    readCPM_HI();
    readCPM_LO();
}

unsigned int GeigerCounter::convertReadBytes(unsigned char* buf_ptr){
    unsigned int conv_val = 0;
    for (int i=0; i<4; i++){
        conv_val = (conv_val << 8) | buf_ptr[i];
    }
    return conv_val;
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

void GeigerCounter::readCPM(){
    unsigned char* buf_ptr; //To store the returned pointer
    unsigned int ret_cpm = 0; //For storing the new value of CPM reading;

    port.sendCommand("GETCPM");
    usleep(WAIT_TIME); //Buffer has to fill up;

    if (port.receiveData() == 4){   //CPM is always returned as 4 bytes
        buf_ptr = port.getBuffer();
        ret_cpm = convertReadBytes(buf_ptr);
    }
    cpm = ret_cpm;
}

void GeigerCounter::readCPM_HI(){
    unsigned char* buf_ptr;
    unsigned int ret_cps_hi = 0;

    port.sendCommand("GETCPMH");
    usleep(WAIT_TIME);

    if (port.receiveData() == 4){
        buf_ptr = port.getBuffer();
        ret_cps_hi = convertReadBytes(buf_ptr);
    }
    cpm_hi = ret_cps_hi;
}

void GeigerCounter::readCPM_LO(){
    unsigned char* buf_ptr;
    unsigned int ret_cps_lo = 0;

    port.sendCommand("GETCPML");
    usleep(WAIT_TIME);

    if (port.receiveData() == 4){
        buf_ptr = port.getBuffer();
        ret_cps_lo = convertReadBytes(buf_ptr);
    }
    cpm_hi = ret_cps_lo;
}

void GeigerCounter::readCPS(){
    unsigned char* buf_ptr;
    unsigned int ret_cps = 0;

    port.sendCommand("GETCPS");
    usleep(WAIT_TIME);

    if (port.receiveData() == 4){
        buf_ptr = port.getBuffer();
        ret_cps = convertReadBytes(buf_ptr);
    }
    cps = ret_cps;
}

void GeigerCounter::readVoltage(){
    float ret_voltage = -1.0;

    port.sendCommand("GETVOLT");
    usleep(WAIT_TIME);

    if (port.receiveData() == 5){   //Voltage always is returned as 5 bytes
        std::string tmp_str(reinterpret_cast<char* >(port.getBuffer()));
        tmp_str.pop_back();
        ret_voltage = stof(tmp_str);
    }
    voltage = ret_voltage;
}

//Setters and getters
unsigned int GeigerCounter::getCPM() {return cpm;}
unsigned int GeigerCounter::getCPM_HI() {return cpm_hi;}
unsigned int GeigerCounter::getCPM_LO() {return cpm_lo;}
unsigned int GeigerCounter::getCPS() {return cps;}
float GeigerCounter::getVoltage() {return voltage;}