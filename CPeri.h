#ifndef CPERI_H
#define CPERI_H
#include <Arduino.h>

class CPeri {

public:
        CPeri();
        ~CPeri();
        void begin();
        void send(int r);
        void setDeviceName(char* name);
};
 

#endif