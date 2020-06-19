#ifndef XibTempo_h
#define XibTempo_h
#include <Arduino.h>
class XibTempo
{
private:
public:
    XibTempo(long duration);//create a timer with the time you want in milliseconds
    ~XibTempo();
    void enable();//let the timer works, it's the default
    void disable();//stops the timer
    void execFunctionTimed(void (*f)());//executes the code with the time
    long timeRemaining();//returns the time remaining to complete the cycle
    long millisStart;
    long millisDuration;
    bool enabled;
};



#endif
