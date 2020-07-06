#ifndef XibFrame_h
#define XibFrame_h

#include <LinkedList.h>
#include <XibComponent.h>
#include <XibXcreen.h>
#include <Subject.h>

class XibFrame : public Observer, public Subject
{
private:
public:
    LinkedList<XibComponent *> components;
    int color;
    int maxLayers = 2;
    String name;
    void addComponent(XibComponent &component);
    void draw();
    void drawComponents();
    void Update(Subject &theChangedSubject) override;
};
#endif