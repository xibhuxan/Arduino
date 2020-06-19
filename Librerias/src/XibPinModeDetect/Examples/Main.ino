#include <XibPinModeDetect.h>

XibPinModeDetect myPinMode(5);

void setup()
{
    Serial.begin(9600);
    
    pinMode(5, INPUT_PULLUP);

    Serial.println(myPinMode.getMode());

}

void loop()
{

}
