
#ifndef Xib_Web_h
#define Xib_Web_h

#include "Arduino.h"


class Xib_Web
{

    public:
    Xib_Web();
    void addHead();
    void addLinea(String s);
    void addFoot();
    String getPagina();
    private:
    String pagina;

};

#endif