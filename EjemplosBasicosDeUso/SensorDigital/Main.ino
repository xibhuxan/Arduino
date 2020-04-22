const byte sensorPin = 2; //Entrada del sensor digital

byte sensorValor = 0; //Variable para guardar el valor del sensor

void setup()
{
	pinMode(sensorPin, INPUT); //Configurar el pin como entrada
    Serial.begin(9600); //Habilitar la transmisión serie
}

void loop()
{
	sensorValor = digitalRead(sensorPin); //Leer el valor digital del sensor y guardarlo
    Serial.println(sensorValor); //Enviar el valor del sensor por el puerto serie
}
