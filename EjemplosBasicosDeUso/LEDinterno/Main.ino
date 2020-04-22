//Código copiado del ejemplo blink
void setup()
{
    //Inicializar la variable LED_BUILTIN como una salida,
    //esa variable corresponde al valor numérico 13,
    //se puede sustituir directamente por este número
    pinMode(LED_BUILTIN, OUTPUT);
}

//Función que se repetirá todo el rato
void loop()
{
    //digitalWrite() manipula la escritura de una salida
    digitalWrite(LED_BUILTIN, HIGH); // Enciende la salida correspondiente, HIGH es el valor de encendido, se puede sustituir por 1 o true
    delay(1000);                     // El código se queda congelado aquí un segundo (no es un buen método de espera)
    digitalWrite(LED_BUILTIN, LOW);  // Apaga la salida correspondiente, LOW es el valor de pagado, se puede sustituir por 0 o false
    delay(1000);                     // Se congela el código un segundo
}
