#include <iostream>
#include <unistd.h>
#include "counter.hpp"

int main(void){
    GeigerCounter c1;
    c1.reboot();
    return 0;
}
