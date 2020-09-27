#include <iostream>
#include "counter/counter.hpp"

int main(void){
    GeigerCounter* c1 = new GeigerCounter;
    std::cout << c1->getVoltage() << std::endl << c1->getCPM() << std::endl << c1->getCPM_HI() <<  std::endl << c1->getCPM_LO() << std::endl;
    delete c1;
    return 0;
}
