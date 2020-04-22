// Este código tiene como gran ventaja al no utilizar delay() que el código no se queda congelado, 
//por lo que todo sigue funcionando de manera normal, pero se pueden tener trozos de código que solo se ejecutan cada cierto tiempo

long ultimoTiempo = 0; //Variable para guardar el último tiempo en el que se cumplió la condición
bool estado = false; //Variable para guardar el estado que se quiere en la salida

void setup()
{
    //Inicializar la variable LED_BUILTIN como una salida,
    //esa variable corresponde al valor numérico 13,
    //se puede sustituir directamente por este número
    pinMode(LED_BUILTIN, OUTPUT); //OUTPUT indica que ese pin será una salida
}

//Función que se repetirá todo el rato
void loop()
{
    //Si el tiempo actual menos el último tiempo guardado
    //da como resultado más de 1000,
    //es que ha pasado un segundo,
    //por lo tanto debe entrar en la condición
    if(millis() - ultimoTiempo > 1000){
        ultimoTiempo = millis(); //Se guarda el tiempo actual en el último tiempo
        estado = !estado; //Asignarle a la variable, su estado contrario
        digitalWrite(LED_BUILTIN, estado); //Introducir el estado actual como lo que se quiere escribir en la salida
    }
}
