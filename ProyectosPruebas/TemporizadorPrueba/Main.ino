#include <XibTempo.h>

XibTempo temp1(500); 


bool ledOn = false;

void setup()
{
    pinMode(13, OUTPUT);

}

void loop()
{
	temp1.execFunctionTimed([](){
        digitalWrite(13, ledOn);
        ledOn = !ledOn;
    });
}
