#ifndef XibDebounceEdge_h
#define XibDebounceEdge_h
#include <Arduino.h>
class XibDebounceEdge
{
private:
public:
    XibDebounceEdge(uint32_t debounceDuration);
    ~XibDebounceEdge();
    void whenRisingEdge(bool inputData, void(*f)());
    void whenFallingEdge(bool inputData, void(*f)());
    void whenActive(bool inputData, void(*f)());
    void whenDeactive(bool inputData, void(*f)());
    uint32_t debounceDuration;
    uint32_t lastDebounceTime;
    bool lastInputDataState;
    bool inputDataState;
};
#endif
