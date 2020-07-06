#ifndef XibTempo_h
#define XibTempo_h
#include <Arduino.h>
class XibTempo
{
private:
public:
    XibTempo(uint32_t duration);//create a timer with the time you want in milliseconds
    ~XibTempo();
    void enable();//let the timer works, it's the default
    void disable();//stops the timer
    void execTimedFunction(void (*f)());//executes the code with the time
    bool getTempo();
    void setTime(uint32_t duration);//changes the time of the timer
    uint32_t timeRemaining();//returns the time remaining to complete the cycle
    uint32_t millisStart;
    uint32_t millisDuration;
    bool enabled;
};



#endif
