#include <XibEdges.h>
//You have the integrated option of arduino https://www.luisllamas.es/que-son-y-como-usar-interrupciones-en-arduino/


XibTempo mitemp(1000);

XibEdges miFlaco(8);

void setup()
{
    Serial.begin(9600);
    pinMode(8, INPUT_PULLUP);
    pinMode(13, OUTPUT);
}
bool a;
void loop()
{

    mitemp.execTimedFunction([](){
        digitalWrite(13, a = !a);
    });

    miFlaco.WhenFallingEdge([]() {
        
    });

}
