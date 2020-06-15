#include <XibTemp.h>

XibTemp temp1(1000);

bool ledOn = false;

void setup()
{
    pinMode(13, OUTPUT);
    
	temp1.setFunction([](){
        digitalWrite(13, ledOn);
        ledOn = !ledOn;
    });
    temp1.enable();
}

void loop()
{
	temp1.exec();
}
