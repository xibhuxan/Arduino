#include <XibDebounceEdge.h>

const byte botonPin = 2;
int contador = 0;

bool lecturaBoton = false;

XibDebounceEdge miDetector(10);

void setup()
{
	pinMode(botonPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{
    lecturaBoton = !digitalRead(botonPin);

    //Esta es una manera de ejecutar la funcion

	miDetector.whenRisingEdge(lecturaBoton, [](){
        contador++;
        Serial.println(contador);
    });


    //Esta es otra manera
    /*
    if(miDetector.whenRisingEdge(lecturaBoton)){
        contador++;
        Serial.println(contador);
    }
    */
}
