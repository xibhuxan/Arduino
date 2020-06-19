#include <XibPinModeDetect.h>

XibPinModeDetect::XibPinModeDetect(int pin)
{
    this->pin = pin;
}

XibPinModeDetect::~XibPinModeDetect()
{
}

int XibPinModeDetect::getMode(){

    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *reg, *out;

    reg = portModeRegister(port);
    out = portOutputRegister(port);

    if(!*reg && !*out)return 0; //0,0 -> INPUT
    if(!*reg && *out)return 1;  //0,32 -> INPUT_PULLUP
    if(*reg && !*out)return 2;  //32,0 -> OUTPUT
}