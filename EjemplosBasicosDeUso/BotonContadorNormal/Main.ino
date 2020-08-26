const byte botonPin = 2;

int contador = 0;

bool estadoBoton = false; //Variable para guardar el estado ACTUAL del boton
bool estadoBotonAnterior = false; //Variable para guardar el estado del ciclo ANTERIOR del boton

void setup()
{
	pinMode(botonPin, INPUT_PULLUP); //Usar el boton directo al arduino, sin resistencia
    Serial.begin(9600);
}

void loop()
{
	estadoBoton = !digitalRead(botonPin); //Leer el estado del boton (la exclamacion es porque al tener INPUT_PULLUP se lee en logica negativa el boton, asi que "!" lo cambia a logica positiva)

    if(estadoBoton != estadoBotonAnterior){ //Si el estado del boton es distinto al estado anterior, es que ha cambiado de pisado a no pisado, o viceversa
        if(estadoBoton == HIGH){ //Si el estado del boton esta en HIGH, hace lo que sea, en este caso contar y mostrar por pantalla. Se puede poner "LOW" o "!=", depende de lo que se quiera detectar
            contador++;
            Serial.println(contador);
        }
    }

    estadoBotonAnterior = estadoBoton; //Se le asigna a estadoBotonAnterior el estadoBoton porque en el proximo ciclo de programa pasará a ser el valor viejo
}
