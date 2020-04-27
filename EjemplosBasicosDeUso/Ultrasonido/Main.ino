
//Añadir la libreria que facilita el uso del ultrasonido
#include <NewPing.h>

const byte trigPin = 2; //Pin del trigger
const byte echoPin = 3; //Pin del echo
const int distanciaMAX = 400; //Distancia máxima que va a detectar

NewPing miSonar(trigPin, echoPin, distanciaMAX); //Creación del objeto con los parámetros que necesita

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    Serial.println(miSonar.ping_cm()); //Imprimir por puerto serie los centímetros que está detectando el sensor
    delay(500);
}
