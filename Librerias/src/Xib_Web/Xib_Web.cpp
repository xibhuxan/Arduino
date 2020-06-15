 
#include "Arduino.h"
#include "Xib_Web.h"

Xib_Web::Xib_Web(){
    pagina = "";
}

void Xib_Web::addHead(){
    pagina += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<meta charset='utf-8'/><html>\r\n";
}

void Xib_Web::addLinea(String s){
    pagina += s;
}

void Xib_Web::addFoot(){
    pagina += "</html>\n";
}

String Xib_Web::getPagina(){
    return pagina;
}