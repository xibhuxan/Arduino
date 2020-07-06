#include <XibTempo.h>

XibTempo::XibTempo(uint32_t duration)
{
    millisDuration = duration;
    enabled = true;
}

XibTempo::~XibTempo()
{
}

void XibTempo::enable()
{
    enabled = true;
}
void XibTempo::disable()
{
    enabled = false;
}
void XibTempo::execTimedFunction(void (*f)())
{
    if (enabled && (millis() - millisStart >= millisDuration))
    {
        millisStart = millis();
        f();
    }
}
bool XibTempo::getTempo()
{
    if (enabled && (millis() - millisStart >= millisDuration))
    {
        millisStart = millis();
        return true;
    }
    else
    {
        return false;
    }
}
void XibTempo::setTime(uint32_t duration)
{
    millisDuration = duration;
}
uint32_t XibTempo::timeRemaining()
{
    return (millisStart + millisDuration) - millis();
}
