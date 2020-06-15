#include <XibTemp.h>

XibTemp::XibTemp(long duration)
{
    millisDuration = duration;
    enabled = false;
}

XibTemp::~XibTemp()
{
}

void XibTemp::setFunction(void (*f)())
{
    MyFunction = f;
}

void XibTemp::enable()
{
    enabled = true;
}
void XibTemp::disable()
{
    enabled = false;
}
void XibTemp::exec()
{
    if(enabled && (millis() - millisStart >= millisDuration)){
        millisStart = millis();
        MyFunction();
    }
}
long XibTemp::timeRemaining()
{
    return (millisStart + millisDuration) - millis();
}
