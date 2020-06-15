#ifndef Subject_h
#define Subject_h
#include <LinkedList.h>
#include <Observer.h>

#define MAX_INDEX 10
class Subject
{
private:
    LinkedList <Observer*> observers;
public:
    virtual ~Subject() = default;
    void Attach(Observer &o){observers.Append(&o);};

    void NotifyAll();
    void Notify(Observer *o);
};

#endif
