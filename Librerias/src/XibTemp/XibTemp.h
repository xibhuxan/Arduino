#ifndef XibTemp_h
#define XibTemp_h
#include <Arduino.h>
class XibTemp
{
private:
public:
    XibTemp(long duration);//create a timer with the time you want in milliseconds
    ~XibTemp();
    void setFunction(void(*f)());//set what have to do the timer, remember the [](){} symbols as in the example
    void enable();//let the timer works
    void disable();//stops the timer
    void exec();//executes the code inside "setFunction"
    long timeRemaining();//returns the time remaining to complete the cycle
    long millisStart;
    long millisDuration;
    bool enabled;
    void (*MyFunction)();
};



#endif