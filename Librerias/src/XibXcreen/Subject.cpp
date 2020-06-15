#include <Subject.h>

void Subject::NotifyAll()
{
    int max = observers.getLength();
    Observer *o;
    for (int i = 0; i < max; i++)
    {
        o = observers.getElement(i);
        o->Update(*this);
    }
}
void Subject::Notify(Observer *o)
{

    o->Update(*this);
}
