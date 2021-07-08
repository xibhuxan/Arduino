#ifndef XibTimer_h
#define XibTimer_h
#include <Arduino.h>
class XibTimer
{
private:
    uint32_t lastMillisTime;
    uint32_t timerDuration;
    bool enabled;

public:
    //create a timer with the time you want in milliseconds
    XibTimer(uint32_t duration);
    XibTimer();
    ~XibTimer();

    //let the cycle functions to execute code
    void enable();

    //stop cycle functions
    void disable();

    //executes the code every time the cycle is completed
    void cycleCompleted(void (*f)());

    //return true every time the cycle is completed
    bool cycleCompleted();

    //changes the time of the timer
    void setTime(uint32_t duration);

    //get the current timer duration
    uint32_t getTime();

    //returns the time remaining to complete the cycle
    uint32_t timeRemaining();
};

#endif
