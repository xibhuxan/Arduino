const byte actuadorPin = 3; //Pin para utilizar la salida analógica, marcado con ~ en la placa

void setup()
{
	pinMode(actuadorPin, OUTPUT); //Configurar el pin como una salida
}

void loop()
{
	analogWrite(actuadorPin, 40); //Asignarle al pin un valor de 40 sobre 255
    delay(1000); //Congelar el código 1 segundo
    analogWrite(actuadorPin, 250); //Asignarle al pin un valor de 250 sobre 255
    delay(1000);
}
