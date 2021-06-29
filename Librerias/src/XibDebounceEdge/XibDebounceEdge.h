#ifndef XibDebounceEdge_h
#define XibDebounceEdge_h
#include <Arduino.h>
class XibDebounceEdge
{
private:
public:
    XibDebounceEdge(uint16_t debounceDuration);
    ~XibDebounceEdge();
    //void functions
    void whenRisingEdge(bool inputData, void(*f)());
    void whenFallingEdge(bool inputData, void(*f)());
    void whenActive(bool inputData, void(*f)());
    void whenDeactive(bool inputData, void(*f)());
    //bool functions
    bool whenRisingEdge(bool inputData);
    bool whenFallingEdge(bool inputData);
    bool whenActive(bool inputData);
    bool whenDeactive(bool inputData);
    uint16_t debounceDuration;
    uint16_t lastDebounceTime;
    bool lastInputDataState;
    bool inputDataState;
};
#endif
