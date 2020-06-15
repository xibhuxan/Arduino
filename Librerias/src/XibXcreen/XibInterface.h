#ifndef XibInterface_h
#define XibInterface_h

//Librerías necesarias
#include <Arduino.h>

#include <LinkedList.h>
#include <XibXcreenValues.h>
#include <XibFrame.h>
#include <XibXcreen.h>
#include <Subject.h>

#define PRECISION_AMOUNT 5

class XibInterface : public Subject
{
private:
    long tiempoContaje;
    int indicePrecision;
    int valoresPrecision[PRECISION_AMOUNT];
    void rellenarArray(int valor);
    LinkedList<XibFrame *> frames;
    LinkedList<XibComponent *> components;
    int currentFrameNumber = -1;
    int maxFrames;
    XibFrame *currentFrame;


public:
    void refreshTouchValues();
    void refreshTouchValues(int tiempo);
    bool isScreenTouched();
    void drawFrame(int x);
    void drawCurrentFrame();
    void drawNewFrame(int x);
    void addFrame(XibFrame &f);
    void addComponent(XibComponent &c);
    XibFrame *getFrame(int x);
    
    int getCurrentFrame();
    void setCurrentFrame(int x);
    int getNumFrames();
};

#endif
