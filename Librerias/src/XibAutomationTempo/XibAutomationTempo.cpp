#include <XibAutomationTempo.h>
#include <XibDebounceEdge.h>
XibTempoIM::XibTempoIM(uint32_t duration)
{
    tempoTime = duration;
}

XibTempoIM::~XibTempoIM()
{
}

void XibTempoIM::setTime(uint32_t duration)
{
    tempoTime = duration;
}
bool XibTempoIM::timer(bool active){

}
bool XibTempoIM::timer(bool active, bool reset){

}
bool XibTempoIM::timer(bool active, bool reset, void (*f)()){

}
bool XibTempoIM::timer(bool active, void (*f)()){

}