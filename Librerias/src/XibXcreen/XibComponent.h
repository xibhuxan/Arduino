#ifndef XibComponent_h
#define XibComponent_h
#include <Subject.h>
#include <XibXcreen.h>
#include <XibXcreenValues.h>

class XibComponent : public Observer, public Subject
{
private:
public:
    int x;
    int y;
    int xPercent;
    int yPercent;
    int layer = 1;
    int color;
    void (*ExtraDraw)();
    virtual void DrawMySelf();
    virtual void Update(Subject &theChangedSubject);
    virtual bool CoorInsideMe(int x, int y);
    void setExtraDraw(void (*f)());
};

/*Rectangulo*/
class XibCompRect : public XibComponent
{
private:
public:
    int width;
    int height;
    int x2Percent;
    int y2Percent;
    int textColor = BLACK;
    int textSize;
    String text;
    bool textFirst;
    void setCoorWH(int x, int y, int width, int height);
    void setCoor(int x1, int y1, int x2, int y2);
    void setCoorPercent(int xPercent, int yPercent, int secondXpercent, int secondYpercent);
    void DrawMySelf() override;
    bool CoorInsideMe(int x, int y) override;
    void Update(Subject &) override;
};

#endif