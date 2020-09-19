#include <string>

#define buffer_size 4096

class SerialPort{
    private:
        int port_num, baud_rate;
        unsigned char buf[buffer_size];
        std::string mode;

    public:
        SerialPort();
        SerialPort(int p_n, int bd_rate, std::string md);
        ~SerialPort();
        int receiveData();
        void sendCommand(std::string cmd);
        void setPortNumber(int p_n);
        void setBaudRate(int bd_rate);
        void setMode(const char* md);
        void setMode(std::string md);
        int getPortNumber();
        int getBaudRate();
        std::string getMode();

    private:
        void correctMessage(std::string &msg);
        void openPort();
};
