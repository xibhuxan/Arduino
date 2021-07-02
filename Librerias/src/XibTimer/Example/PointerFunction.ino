#include <XibTimer.h>

XibTimer temp1(500);

bool ledState = false;

void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{

    //In this case you use a function created previously, put the name and use parentheses with parameters if needed
    temp1.cycleCompleted(changeLedState);
}

void changeLedState()
{
    //Change state ledState. Assign the same var with "!" save the contrary value. And then use its value. (First change, second use)
    ledState = !ledState;
    digitalWrite(13, ledState);
}