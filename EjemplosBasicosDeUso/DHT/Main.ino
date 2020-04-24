
//Librería en la carpeta de librerías
#include <dht.h> //Incluir la librería correspondiente, más información del componente en https://lastminuteengineers.com/dht11-module-arduino-tutorial/
const byte DHTpin = 2; //Pin del sensor

dht DHT; //Crear un objeto de la librería

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	DHT.read11(DHTpin); //Hacer que el objeto lea como dht11, en el pin indicado

    float temp = DHT.temperature; //Coger la temperatura que ha leído y guardarla
    float hum = DHT.humidity; //Coger la humedad que ha leído y guardarla

    //Mandar al pc
    Serial.print("Temp: ");
    Serial.println(temp);
    Serial.print("Hum: ");
    Serial.println(hum);
    delay(1000);

}
