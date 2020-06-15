
#include <Arduino.h>
#include <XibInterface.h>

void XibInterface::refreshTouchValues()
{
    refreshTouchValues(1);
}
void XibInterface::refreshTouchValues(int tiempo)
{

    if (millis() - tiempo > tiempoContaje)
    {
        tiempoContaje = millis();
        XibXcreen::tsp = XibXcreen::ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        int x;
        int y;

        switch (XibXcreen::tft.getRotation())
        {
        case 0:
            x = map(XibXcreen::tsp.x, TS_MINX, TS_MAXX, 0, LONG_SIDE);
            y = map(XibXcreen::tsp.y, TS_MINY, TS_MAXY, SHORT_SIDE, 0);
            XibXcreen::myxPercent = map(y, 0, SHORT_SIDE, 0, 100);
            XibXcreen::myyPercent = map(x, 0, LONG_SIDE, 0, 100);
            XibXcreen::tsp.x = y;
            XibXcreen::tsp.y = x;

            break;
        case 1:
            x = map(XibXcreen::tsp.x, TS_MINX, TS_MAXX, 0, LONG_SIDE);
            y = map(XibXcreen::tsp.y, TS_MINY, TS_MAXY, 0, SHORT_SIDE);
            XibXcreen::myxPercent = map(x, 0, LONG_SIDE, 0, 100);
            XibXcreen::myyPercent = map(y, 0, SHORT_SIDE, 0, 100);
            XibXcreen::tsp.x = x;
            XibXcreen::tsp.y = y;

            break;
        case 2:
            x = map(XibXcreen::tsp.x, TS_MINX, TS_MAXX, LONG_SIDE, 0);
            y = map(XibXcreen::tsp.y, TS_MINY, TS_MAXY, 0, SHORT_SIDE);
            XibXcreen::myxPercent = map(y, 0, SHORT_SIDE, 0, 100);
            XibXcreen::myyPercent = map(x, 0, LONG_SIDE, 0, 100);
            XibXcreen::tsp.x = y;
            XibXcreen::tsp.y = x;

            break;
        case 3:
            x = map(XibXcreen::tsp.x, TS_MINX, TS_MAXX, LONG_SIDE, 0);
            y = map(XibXcreen::tsp.y, TS_MINY, TS_MAXY, SHORT_SIDE, 0);
            XibXcreen::myxPercent = map(x, 0, LONG_SIDE, 0, 100);
            XibXcreen::myyPercent = map(y, 0, SHORT_SIDE, 0, 100);
            XibXcreen::tsp.x = x;
            XibXcreen::tsp.y = y;

            break;
        }

        rellenarArray(XibXcreen::tsp.z);

        if (isScreenTouched()){
            Notify(currentFrame);
            for (int i = 0; i < components.getLength(); i++)
            {
                XibComponent *comp = components.getElement(i);
                if(comp->CoorInsideMe(XibXcreen::tsp.x, XibXcreen::tsp.y))
                Notify(comp);
            }
            
        }
            
    }
}

void XibInterface::rellenarArray(int valor)
{
    valoresPrecision[indicePrecision] = valor;

    indicePrecision++;
    if (indicePrecision >= PRECISION_AMOUNT)
    {
        indicePrecision = 0;
    }
}

bool XibInterface::isScreenTouched()
{

    bool pisada = false;
    for (int i = 0; i < PRECISION_AMOUNT; i++)
    {
        if (valoresPrecision[i] != 0)
        {
            pisada = true;
            break;
        }
    }

    return pisada && XibXcreen::tsp.z > MINPRESSURE;
}

void XibInterface::drawFrame(int x)
{

    if (currentFrameNumber != x)
    {
        currentFrame = frames.getElement(x);
        currentFrame->draw();
        currentFrameNumber = x;
    }
    for (int i = 0; i < components.getLength(); i++)
    {
        components.getElement(i)->DrawMySelf();
    }

    currentFrame->drawComponents();
}
void XibInterface::drawCurrentFrame()
{
    drawFrame(currentFrameNumber);
}
void XibInterface::drawNewFrame(int x)
{
    currentFrame = frames.getElement(x);
    currentFrame->draw();
    for (int i = 0; i < components.getLength(); i++)
    {
        components.getElement(i)->DrawMySelf();
    }

    currentFrame->drawComponents();
}

void XibInterface::addFrame(XibFrame &f)
{
    XibFrame *myF = &f;
    frames.Append(myF);
    Attach(*myF);
    maxFrames++;
}
void XibInterface::addComponent(XibComponent &c)
{
    XibComponent *myC = &c;
    components.Append(myC);
    Attach(*myC);
}

XibFrame *XibInterface::getFrame(int x)
{
    return frames.getElement(x);
}
int XibInterface::getCurrentFrame()
{
    return currentFrameNumber;
}
void XibInterface::setCurrentFrame(int x)
{
    currentFrameNumber = x;
    drawNewFrame(currentFrameNumber);
}
int XibInterface::getNumFrames()
{
    return maxFrames;
}

//Funcion original, no tocar
/*
TSPoint waitTouch()
{
    TSPoint p;
    do
    {
        p = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
    } while ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE));
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 320);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 240);
    return p;
}
*/