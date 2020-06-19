#ifndef XibPinModeDetect_h
#define XibPinModeDetect_h
#include <Arduino.h>

class XibPinModeDetect
{
private:
public:
    XibPinModeDetect(int pin);
    ~XibPinModeDetect();
    int getMode();
    int pin;
};



#endif