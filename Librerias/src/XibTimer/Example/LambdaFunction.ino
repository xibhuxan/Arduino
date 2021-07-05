#include <XibTimer.h>

XibTimer temp1(500);

bool ledState = false;

void setup()
{
    pinMode(13, OUTPUT);
}

void loop()
{
    //In this case it's a lambda funcition, you write it directly (with its symbols), without a name, as a parameter.
    //To use functions with parameters, put the function inside the lambda
    temp1.cycleCompleted([]() {
        //Do stuff here
        changeLedState(/*possible parameters*/);
    });
}

//Change state ledState. Assign the same var with "!" save the contrary value. And then use its value. (First change, second use)
void changeLedState(/*possible parameters*/)
{
    ledState = !ledState;
    digitalWrite(13, ledState);
}