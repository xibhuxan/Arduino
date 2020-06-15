#ifndef XibXcreen_h
#define XibXcreen_h

#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <XibXcreenValues.h>
class XibXcreen
{
public:
    static TouchScreen ts;
    static Adafruit_TFTLCD tft;
    static TSPoint tsp;
    static int myxPercent;
    static int myyPercent;
    static TSPoint pixelToPercent(int x, int y)
    {
        TSPoint point;
        if (XibXcreen::tft.getRotation() == 0 || XibXcreen::tft.getRotation() == 2)
        {
            point.x = x * 100 / SHORT_SIDE;
            point.y = y * 100 / LONG_SIDE;
        }
        if (XibXcreen::tft.getRotation() == 1 || XibXcreen::tft.getRotation() == 3)
        {
            point.x = x * 100 / LONG_SIDE;
            point.y = y * 100 / SHORT_SIDE;
        }
        return point;
    }
    static TSPoint percentToPixel(int myxPercent, int myyPercent)
    {
        TSPoint point;
        if (XibXcreen::tft.getRotation() == 0 || XibXcreen::tft.getRotation() == 2)
        {
            point.x = myxPercent * SHORT_SIDE / 100;
            point.y = myyPercent * LONG_SIDE / 100;
        }
        if (XibXcreen::tft.getRotation() == 1 || XibXcreen::tft.getRotation() == 3)
        {
            point.x = myxPercent * LONG_SIDE / 100;
            point.y = myyPercent * SHORT_SIDE / 100;
        }
        return point;
    }
};

#endif
