//Código copiado del ejemplo blink

const byte ledPin = 3;

void setup()
{
    //Inicializar la variable ledPin como una salida,
    //esa variable corresponde al valor numérico 3,
    //se puede sustituir directamente por este número, pero lo correcto es utilizar variables
    pinMode(ledPin, OUTPUT);
}

//Función que se repetirá todo el rato
void loop()
{
    //digitalWrite() manipula la escritura de una salida
    digitalWrite(ledPin, HIGH); // Enciende la salida correspondiente, HIGH es el valor de encendido, se puede sustituir por 1 o true
    delay(1000);                     // El código se queda congelado aquí un segundo (no es un buen método de espera)
    digitalWrite(ledPin, LOW);  // Apaga la salida correspondiente, LOW es el valor de pagado, se puede sustituir por 0 o false
    delay(1000);                     // Se congela el código un segundo
}
