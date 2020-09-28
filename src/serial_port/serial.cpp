#include "rs232.h"
#include "serial.hpp"
#include "../rapidjson/document.h"
#include "../rapidjson/filereadstream.h"
#include <string>

#define buffer_size 4096

SerialPort::SerialPort(){
    if (!loadConfig()){ //If loading config fails fall back to the defaults
        printf("Loading config failed! Using defaults.\n");
        setPortNumber(16); //Default port corresponds to /dev/USB0
        setBaudRate(115200); //That's the default baud rate of the geiger counter
        setMode("8N1");
        openPort();
    }
    else openPort();

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

bool SerialPort::loadConfig(){
    //File loading and parsing
    std::string configFileName = "config.json";
    FILE* configFile = fopen(configFileName.c_str(), "rb");

    if (configFile == NULL) {
        return false; //Return failure 
    }

    //Parsing the config into DOM structure
    char json_buffer[65536]; //Make it smaller?
    rapidjson::FileReadStream is(configFile, json_buffer, sizeof(json_buffer));
    rapidjson::Document parsedConfig;
    parsedConfig.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

    //Structure check and eventual config loading
    if (parsedConfig.HasMember("geiger")){
        bool properConfig = true;
        if (!parsedConfig["geiger"].HasMember("port_number")) properConfig = false;
        if (!parsedConfig["geiger"].HasMember("baud_rate")) properConfig = false;
        if (!parsedConfig["geiger"].HasMember("mode")) properConfig = false;
        
        if (properConfig){
            setPortNumber(parsedConfig["geiger"]["port_number"].GetInt());
            setBaudRate(parsedConfig["geiger"]["baud_rate"].GetInt());
            setMode(parsedConfig["geiger"]["mode"].GetString());
            return true;
        }
    }
    return false;
}

void SerialPort::openPort(){
    RS232_OpenComport(port_num, baud_rate, mode.c_str(), 0);
}

void SerialPort::sendCommand(std::string cmd){
    correctMessage(cmd);
    RS232_cputs(port_num, cmd.c_str()); //String needs to be null-terminated
}

void SerialPort::correctMessage(std::string &msg){
    msg.insert(0, "<");
    msg.append(">>");
}

int SerialPort::receiveData(){
    int n = RS232_PollComport(port_num, buf, buffer_size-1);
    if (n>0){
        buf[n] = 0; //terminate the buffer
    }
    return n; //It returnes the numbers of bytes received
}

//Setters and getters
void SerialPort::setPortNumber(int p_n) {port_num = p_n;}
void SerialPort::setBaudRate(int bd_rate) {baud_rate = bd_rate;}
void SerialPort::setMode(const char* md) {mode = md;}
void SerialPort::setMode(std::string md) {mode = md.c_str();}
unsigned char* SerialPort::getBuffer() {return buf;}
int SerialPort::getPortNumber() {return port_num;}
int SerialPort::getBaudRate() {return baud_rate;}
std::string SerialPort::getMode() {return mode;}
