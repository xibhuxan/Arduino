#include <XibFrame.h>

void XibFrame::addComponent(XibComponent &component)
{
    XibComponent *myC = &component;
    components.Append(myC);
    Attach(*myC);
}

void XibFrame::draw()
{
    XibXcreen::tft.fillScreen(color);
}

void XibFrame::drawComponents()
{

    for (int i = 0; i <= maxLayers; i++)
    {
        
        for (int j = 0; j < components.getLength(); j++)
        {
            XibComponent *comp = components.getElement(j);
            if (comp->layer == i)
            {
                comp->DrawMySelf();
            }
        }
    }
}



void XibFrame::Update(Subject &theChangedSubject)
{
    int x = XibXcreen::tsp.x;
    int y = XibXcreen::tsp.y;
    
    bool compMaxLayer = false;
    
    for (int i = maxLayers; i >= 0 && !compMaxLayer; i--)
    {
        for (int j = 0; j < components.getLength() && !compMaxLayer; j++)
        {
            XibComponent *comp = components.getElement(j);
            if (comp->CoorInsideMe(x, y) && comp->layer == i)
            {
                Notify(comp);
                compMaxLayer = true;
            }
        }
    }
    
}