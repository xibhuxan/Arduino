
#include <TFT.h>
#include <SPI.h>

#define cs 10
#define dc 9
#define rst 8

#define WIDTH 160
#define HEIGH 128

TFT p = TFT(cs, dc, rst);

void setup()
{
	p.begin();
    p.background(255,255,255);
    p.setTextSize(2);
    p.stroke(0,0,0);
    p.text("cosa", 40, HEIGH/3);
    p.text("cosa", 10,HEIGH/2 );
}

void loop()
{
	
}
