#include <XibTimer.h>

XibTimer temp1(500);

void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{
    //In this case it's a lambda funcition, you write it directly (with its symbols), without a name, as a parameter.
    //To use functions with parameters, put the function inside the lambda. And of course, more code if you want
    temp1.cycleCompleted([]() {
        //Do stuff here
        changeLedState(HIGH);
    });
}

//Give to led in pin 13 the "state" value
void changeLedState(bool state)
{
    digitalWrite(13, state);
}