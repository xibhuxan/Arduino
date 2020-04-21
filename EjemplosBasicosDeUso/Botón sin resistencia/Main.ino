const byte botonPin = 2; //Pin al que está conectado el botón
const byte ledPin = 13; //Pin al que está conectado el led (led interno)

byte botonEstado = 0; //Variable donde se guarda el estado actual del botón

void setup()
{
	pinMode(botonPin, INPUT_PULLUP); //Colocar el pin 2 como una entrada pullup, 
    //por lo que se activa una resistencia interna y ya no se necesita una por fuera
    pinMode(ledPin, OUTPUT); //Colocar el pin 13 como una salida
}

void loop()
{
	botonEstado = !digitalRead(botonPin); //Leed el pin del botón, y asignarlo al estado. 
    //Se le asigna el contrario ya que al usar el pullup, va en sentido contrario
    if(botonEstado == 1){ //Si el estado es 1, enciende el led
        digitalWrite(ledPin, HIGH);
    }else{ //Si el estado es 0, apaga el led
        digitalWrite(ledPin, LOW);
    }
}
