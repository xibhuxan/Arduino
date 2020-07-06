//https://programacionsiemens.com/temporizadores-tipos-step-7/

#ifndef XibAutomationTempo_h
#define XibAutomationTempo_h
#include <XibDebounceEdge.h>

class XibTempoIM
{
private:
public:
    XibTempoIM(uint32_t duration);
    ~XibTempoIM();
    void setTime(uint32_t duration);
    bool timer(bool active);
    bool timer(bool active, bool reset);
    bool timer(bool active, bool reset, void (*f)());
    bool timer(bool active, void (*f)());
    XibDebounceEdge debounce;
    uint32_t tempoTime;
    bool tempoActive;
    bool tempoKeepActive;
    bool tempoReset;
};





#endif
