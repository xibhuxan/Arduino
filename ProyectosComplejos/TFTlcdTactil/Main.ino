

#include <XibXcreen.h>
#include <XibInterface.h>
#include <XibFrame.h>
#include <XibComponent.h>

TouchScreen XibXcreen::ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_TFTLCD XibXcreen::tft = Adafruit_TFTLCD(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TSPoint XibXcreen::tsp;
int XibXcreen::myxPercent = 0;
int XibXcreen::myyPercent = 0;

//Graphical interface controller
XibInterface xcn;

//Frames or Screens
XibFrame Frame0, Frame1, Frame2, Frame3, Frame4, Frame5, Frame6;

//Buttons
//General
XibCompRect Menu1, Menu2, Menu3, Menu4;
//Frame0 Frame list of menu
XibCompRect ButtonF01, ButtonF02; //List of frames
//Frame1 Movable square
XibCompRect ButtonF1;
//Frame2 Paint
XibCompRect ButtonF2Increase, ButtonF2Decrease, ButtonF2BrushSize, ButtonF2Color, ButtonF2PictureSpace; //Increase, decrease brush size, change brush color.

//Events
//General
Event Menu1EV, Menu2EV, Menu3EV, Menu4EV;
//Frame0
Event ButtonF01EV, ButtonF02EV;
//Frame1
Event Button1EV;
//Frame2
Event ButtonF2IncreaseEV, ButtonF2DecreaseEV, ButtonF2ColorEV, FramePaint;

//Paint Logic
int BrushSize = 1;
int BrushColor = BLACK;
int BrushColorIndex;
long BrushTimeBlock;

void setup()
{
    XibXcreen::tft.reset();
    XibXcreen::tft.begin(MODEL);
    XibXcreen::tft.setRotation(0);

    //FRAMES
    //Frame0
    Frame0.color = YELLOW;
    Frame0.name = F("Menu principal");
    Frame0.addComponent(ButtonF01);
    Frame0.addComponent(ButtonF02);

    //Frame1
    Frame1.color = WHITE;
    Frame1.name = F("Cuadro movible");
    Frame1.addComponent(ButtonF1);

    //Frame2
    Frame2.color = WHITE;
    Frame2.name = F("Paint");
    Frame2.addComponent(ButtonF2Increase);
    Frame2.addComponent(ButtonF2Decrease);
    Frame2.addComponent(ButtonF2Color);
    Frame2.addComponent(ButtonF2BrushSize);
    Frame2.addComponent(ButtonF2PictureSpace);

    //General components
    Menu1EV.setFunc([]() {
        if (xcn.getCurrentFrame() != 0)
        {
            xcn.setCurrentFrame(xcn.getCurrentFrame() - 1);
        }
        else
        {
            xcn.setCurrentFrame(xcn.getNumFrames() - 1);
        }
    });

    Menu2EV.setFunc([]() {
        XibXcreen::tft.setRotation((XibXcreen::tft.getRotation() + 1) % 4);
        xcn.drawNewFrame(xcn.getCurrentFrame());
    });

    Menu3EV.setFunc([]() {
        xcn.setCurrentFrame(0);
    });

    Menu4EV.setFunc([]() {
        if (xcn.getCurrentFrame() != xcn.getNumFrames() - 1)
        {
            xcn.setCurrentFrame(xcn.getCurrentFrame() + 1);
        }
        else
        {
            xcn.setCurrentFrame(0);
        }
    });

    Menu1.color = RED;
    Menu1.setCoorPercent(0, 25, 90, 100);
    Menu1.textColor = BLACK;
    Menu1.textSize = 2;
    Menu1.text = F("Atras");
    Menu1.Attach(Menu1EV);

    Menu2.color = BLUE;
    Menu2.setCoorPercent(25, 50, 90, 100);
    Menu2.textColor = BLACK;
    Menu2.textSize = 2;
    Menu2.text = F("Rotar");
    Menu2.Attach(Menu2EV);

    Menu3.color = GREEN;
    Menu3.setCoorPercent(50, 75, 90, 100);
    Menu3.textColor = BLACK;
    Menu3.textSize = 2;
    Menu3.text = F("Menu");
    Menu3.Attach(Menu3EV);

    Menu4.color = MAGENTA;
    Menu4.setCoorPercent(75, 100, 90, 100);
    Menu4.textColor = BLACK;
    Menu4.textSize = 2;
    Menu4.text = F("Sig");
    Menu4.Attach(Menu4EV);

    xcn.addComponent(Menu1);
    xcn.addComponent(Menu2);
    xcn.addComponent(Menu3);
    xcn.addComponent(Menu4);

    //Components Frame0

    ButtonF01EV.setFunc([]() {
        xcn.setCurrentFrame(1);
    });
    ButtonF02EV.setFunc([]() {
        xcn.setCurrentFrame(2);
    });

    ButtonF01.color = WHITE;
    ButtonF01.setCoorPercent(15, 85, 10, 20);
    ButtonF01.text = Frame1.name;
    ButtonF01.textSize = 2;
    ButtonF01.Attach(ButtonF01EV);

    ButtonF02.color = WHITE;
    ButtonF02.setCoorPercent(20, 80, 30, 40);
    ButtonF02.text = Frame2.name;
    ButtonF02.textSize = 2;
    ButtonF02.Attach(ButtonF02EV);

    //Components Frame1
    Button1EV.setFunc([]() {
        int miColor = ButtonF1.color;
        ButtonF1.color = Frame1.color;
        ButtonF1.DrawMySelf();
        
        ButtonF1.color = miColor;
        TSPoint one;
        one.x = XibXcreen::myxPercent;
        one.y = XibXcreen::myyPercent;
        int tam = 10;
        ButtonF1.setCoorPercent(one.x - tam, one.x + tam, one.y - tam, one.y + tam);
        ButtonF1.DrawMySelf();
    });

    ButtonF1.color = BLACK;
    ButtonF1.setCoorPercent(30, 60, 40, 60);
    ButtonF1.Attach(Button1EV);

    //Components Frame2
    ButtonF2IncreaseEV.setFunc([]() {
        if (millis() - BrushTimeBlock > 100)
        {

            BrushTimeBlock = millis();
            BrushSize += 1;
            ButtonF2BrushSize.text = BrushSize;
            ButtonF2BrushSize.DrawMySelf();
            ButtonF2Increase.DrawMySelf();
        }
    });
    ButtonF2DecreaseEV.setFunc([]() {
        if (millis() - BrushTimeBlock > 100)
        {

            BrushTimeBlock = millis();
            BrushSize -= 1;
            ButtonF2BrushSize.text = BrushSize;
            ButtonF2BrushSize.DrawMySelf();
            ButtonF2Decrease.DrawMySelf();
        }
    });
    ButtonF2ColorEV.setFunc([]() {
        if (millis() - BrushTimeBlock > 500)
        {

            BrushTimeBlock = millis();
            BrushColorIndex = (BrushColorIndex + 1) % 8;
            switch (BrushColorIndex)
            {
            case 0:
                BrushColor = BLACK;
                break;
            case 1:
                BrushColor = BLUE;
                break;
            case 2:
                BrushColor = RED;
                break;
            case 3:
                BrushColor = GREEN;
                break;
            case 4:
                BrushColor = CYAN;
                break;
            case 5:
                BrushColor = MAGENTA;
                break;
            case 6:
                BrushColor = YELLOW;
                break;
            case 7:
                BrushColor = WHITE;
                break;
            }
            ButtonF2Color.color = BrushColor;
            ButtonF2Color.DrawMySelf();
        }
    });

    FramePaint.setFunc([]() {
        XibXcreen::tft.fillCircle(XibXcreen::tsp.x, XibXcreen::tsp.y, BrushSize, BrushColor);
    });

    ButtonF2Increase.setCoorPercent(0, 10, 0, 10);
    ButtonF2Increase.color = RED;
    ButtonF2Increase.Attach(ButtonF2IncreaseEV);
    ButtonF2Increase.setExtraDraw([](){
        XibXcreen::tft.fillRect(ButtonF2Increase.xPercent + 3, ButtonF2Increase.yPercent + 12, 16, 4, BLACK);
        XibXcreen::tft.fillRect(ButtonF2Increase.xPercent + 9, ButtonF2Increase.yPercent + 4, 4, 20, BLACK);
    });

    ButtonF2BrushSize.setCoorPercent(10, 30, 0, 10);
    ButtonF2BrushSize.color = MAGENTA;
    ButtonF2BrushSize.text = BrushSize;
    ButtonF2BrushSize.textSize = 2;

    ButtonF2Decrease.setCoorPercent(30, 40, 0, 10);
    ButtonF2Decrease.color = BLUE;
    ButtonF2Decrease.Attach(ButtonF2DecreaseEV);
    ButtonF2Decrease.setExtraDraw([](){
        XibXcreen::tft.fillRect(ButtonF2Decrease.xPercent + 45, ButtonF2Decrease.yPercent + 12, 17, 5, BLACK);
    });

    ButtonF2Color.setCoorPercent(90, 100, 0, 10);
    ButtonF2Color.color = BrushColor;
    ButtonF2Color.Attach(ButtonF2ColorEV);

    ButtonF2PictureSpace.setCoorPercent(0, 100, 10, 90);
    ButtonF2PictureSpace.color = WHITE;
    ButtonF2PictureSpace.Attach(FramePaint);

    //Add frames inside interface
    xcn.addFrame(Frame0);
    xcn.addFrame(Frame1);
    xcn.addFrame(Frame2);
    xcn.drawNewFrame(0);
}

void loop()
{
    xcn.refreshTouchValues();
}
