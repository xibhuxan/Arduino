//https://riptutorial.com/es/cplusplus/example/24695/patron-observador
#ifndef Observer_h
#define Observer_h
#include <XibXcreen.h>

class Subject;

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void Update(Subject &) = 0;
    void (*MiFunc)();
};

class Event : public Observer
{
public:
    void Update(Subject &theChangedSubject) override
    {
        MiFunc();
    }
    void setFunc(void(*f)())
    {
        MiFunc = f;
    }
};

#endif
