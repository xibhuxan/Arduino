#include <XibTempo.h>

XibTempo::XibTempo(long duration)
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
void XibTempo::execFunctionTimed(void (*f)())
{
    if(enabled && (millis() - millisStart >= millisDuration)){
        millisStart = millis();
        f();
    }
}
long XibTempo::timeRemaining()
{
    return (millisStart + millisDuration) - millis();
}
