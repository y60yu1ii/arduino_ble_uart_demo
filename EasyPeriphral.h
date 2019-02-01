#ifndef EASYPERIPHRAL_H
#define EASYPERIPHRAL_H
#include <Arduino.h>

class EasyPeriphral {

public:
        EasyPeriphral();
        ~EasyPeriphral();
        void begin();
        void setDeviceName(char* name);
        void broadcast(int_16_t number);
        bool connected();
};
 

#endif