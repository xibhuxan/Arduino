
const byte pinArray[] = {2, 3, 4, 5, 6, 7}; //Pines para los distintos leds

const byte controlLed = 13; // LED de control

int waitNextLed = 100; // Tiempo antes de encender el siguiente LED

int tailLength = 4; // Número de LED-s que permanecen encendidos antes de empezar a apagarlos para formar la cola

int lineSize = 11; // Número de LED-s conectados (que es también el tamaño del array)

void setup() // Configuración de los PIN-es como salida digital
{
  int i;
  pinMode(controlLed, OUTPUT);
  for (i = 0; i < lineSize; i++)
  {
    pinMode(pinArray[i], OUTPUT);
  }
}

void loop()
{
  int i;

  int tailCounter = tailLength;   // Se establece la longitud de la cola en un contador
  digitalWrite(controlLed, HIGH); // Se enciende el LED de control para indicar el inicio del loop

  for (i = 0; i < lineSize; i++)
  {

    digitalWrite(pinArray[i], HIGH); // Se encienden consecutivamente los LED
    delay(waitNextLed);              // Esta variable de tiempo controla la velocidad a la que se mueve la estrella

    if (tailCounter == 0)
    {
      digitalWrite(pinArray[i - tailLength], LOW); // Se apagan los LED-s en función de la longitud de la cola.
    }

    else if (tailCounter > 0)
      tailCounter--;
  }

  for (i = (lineSize - tailLength); i < lineSize; i++)
  {
    digitalWrite(pinArray[i], LOW); // Se apagan los LED

    delay(waitNextLed); // Esta variable de tiempo controla la velocidad a la que se mueve la estrella
  }
}
