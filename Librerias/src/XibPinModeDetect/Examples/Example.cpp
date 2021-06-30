#include <XibPinModeDetect.h>


void setup()
{
    Serial.begin(9600);
    
    pinMode(5, OUTPUT);

    //INPUT = 0
    //INPUT_PULLUP = 1
    //OUTPUT = 2

    Serial.println(XibGetPinMode(5));

}

void loop()
{

}
