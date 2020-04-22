const byte actuadorPin = 2; //Asignar el pin que se utilizará como salida

void setup()
{
    pinMode(actuadorPin, OUTPUT); //Configurar el pin como salida
}

void loop()
{
    digitalWrite(actuadorPin, 1); //poner el pin a 5V
    delay(1000);                  //Bloquear el código 1 segundo
    digitalWrite(actuadorPin, 0); //poner el pin a 0V
    delay(1000);
}
