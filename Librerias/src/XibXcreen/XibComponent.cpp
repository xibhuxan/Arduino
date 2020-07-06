#include <XibComponent.h>

void XibComponent::Update(Subject &theChangedSubject)
{
}
bool XibComponent::CoorInsideMe(int x, int y)
{
}
void XibComponent::DrawMySelf()
{
}

void XibComponent::setExtraDraw(void (*f)())
{
    ExtraDraw = f;
}
/*Boton*/

void XibCompRect::setCoorWH(int x, int y, int width, int height)
{
    TSPoint one, two;
    one = XibXcreen::pixelToPercent(x, y);
    two = XibXcreen::pixelToPercent(width, height);
    this->xPercent = one.x;
    this->yPercent = one.y;
    this->x2Percent = two.x;
    this->y2Percent = two.y;
}
void XibCompRect::setCoor(int x1, int y1, int x2, int y2)
{
    TSPoint one, two;
    one = XibXcreen::pixelToPercent(x1, y1);
    two = XibXcreen::pixelToPercent(x2 - x1, y2 - y1);
    this->xPercent = one.x;
    this->yPercent = one.y;
    this->x2Percent = two.x;
    this->y2Percent = two.y;
}
void XibCompRect::setCoorPercent(int percentX1, int percentX2, int percentY1, int percentY2)
{
    this->xPercent = percentX1;
    this->yPercent = percentY1;
    this->x2Percent = percentX2 - percentX1;
    this->y2Percent = percentY2 - percentY1;
}
void XibCompRect::DrawMySelf()
{
    TSPoint one, two;
    one = XibXcreen::percentToPixel(xPercent, yPercent);
    two = XibXcreen::percentToPixel(x2Percent, y2Percent);
    this->x = one.x;
    this->y = one.y;
    this->width = two.x;
    this->height = two.y;

    XibXcreen::tft.fillRect(x, y, width, height, color);

    int centerRectX = one.x + (two.x / 2); //((two.x - one.x)/2) + one.x;
    int centerTextX = text.length() / 2;

    int centerRectY = one.y + (two.y / 3);

    XibXcreen::tft.setTextColor(textColor);
    XibXcreen::tft.setTextSize(textSize);
    XibXcreen::tft.setCursor(centerRectX - (centerTextX * 6 * textSize), centerRectY);
    if (textFirst)
    {
        XibXcreen::tft.print(text);
        if (ExtraDraw != nullptr)
            ExtraDraw();
    }
    else
    {
        if (ExtraDraw != nullptr)
            ExtraDraw();
        XibXcreen::tft.print(text);
    }
}
bool XibCompRect::CoorInsideMe(int x, int y)
{
    return (x > this->x && x < this->x + width) && (y > this->y && y < this->y + height);
}
void XibCompRect::Update(Subject &)
{
    NotifyAll();
}