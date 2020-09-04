#include <string>

class SerialPort{
    private:
        int port_num, baud_rate;
        unsigned char buf[4096];
        std::string mode;

    public:
        SerialPort();
        SerialPort(int p_n, int bd_rate, std::string md);
        void setPortNumber(int p_n);
        void setBaudRate(int bd_rate);
        void setMode(const char* md);
        void setMode(std::string md);
        int getPortNumber();
        int getBaudRate();
        std::string getMode();
        void openPort();
};
