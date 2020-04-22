const byte sensorPin = A0; //Entrada analógica
int sensorValor = 0; //Variable para guardar los valores de la entrada

void setup()
{
	pinMode(sensorPin, INPUT); //Configurar el pin como entrada
    Serial.begin(9600); //Habilitar la transmisión serie
}

void loop()
{
	sensorValor = analogRead(sensorPin); //Leer el valor analógico del pin y guardarlo
    Serial.println(sensorValor); //Enviar el valor analógico por el puerto serie
}
