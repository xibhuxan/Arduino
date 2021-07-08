#include <XibTimer.h>

XibTimer::XibTimer(uint32_t duration)
{
    timerDuration = duration;
    enabled = true;
}

XibTimer::XibTimer()
{
}

XibTimer::~XibTimer()
{
}

void XibTimer::enable()
{
    enabled = true;
}

void XibTimer::disable()
{
    enabled = false;
}

void XibTimer::cycleCompleted(void (*f)())
{
    if (enabled && (millis() - lastMillisTime >= timerDuration))
    {
        lastMillisTime = millis();
        f();
    }
}

bool XibTimer::cycleCompleted()
{
    if (enabled && (millis() - lastMillisTime >= timerDuration))
    {
        lastMillisTime = millis();
        return true;
    }
    else
    {
        return false;
    }
}

void XibTimer::setTime(uint32_t duration)
{
    timerDuration = duration;
}

uint32_t XibTimer::getTime()
{
    return timerDuration;
}

uint32_t XibTimer::timeRemaining()
{
    return (lastMillisTime + timerDuration) - millis();
}
