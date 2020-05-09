
#include <XibXcreen.h>

XibXcreen scn = XibXcreen();
void setup()
{

    scn.init();
    
    scn.tft.setRotation(0);
   scn.tft.fillScreen(RED);
   scn.tft.setTextColor(BLACK);
}

void loop()
{

    scn.refreshTouchValues();


    int x1 = scn.tsp.x;
    int y1 = scn.tsp.y;

    if (scn.isScreenTouched())
    {
        //tft.fillCircle(x1,y1,3,BLACK);

        int x2 = LONG_SIDE / 2;
        int y2 = SHORT_SIDE / 2;
        int xf = x1 - x2;
        int yf = y1 - y2;
        int d = sqrt(pow((xf), 2) + pow((yf), 2));

        //scn.tft.drawCircle(x2, y2, d, BLACK);
        
        scn.tft.fillRect(0,LONG_SIDE-30,240/3,LONG_SIDE, YELLOW);
        scn.tft.fillRect(240/3,LONG_SIDE-30,240/3*2,LONG_SIDE, BLACK);
        scn.tft.fillRect(240/3*2,LONG_SIDE-30,240/3*3,LONG_SIDE, MAGENTA);

    }
    //tft.fillCircle(x1, y1, 3, BLACK);
}
