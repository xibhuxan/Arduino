#include <XibTimer.h>

XibTimer temp1(500);

bool ledState = false;

void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{

    //It return false until it reaches the selected time
    if (temp1.cycleCompleted())
    {
        //Change state ledState. Assign the same var with "!" save the contrary value. And then use its value. (First change, second use)
        ledState = !ledState;
        digitalWrite(13, ledState);
    }
}
