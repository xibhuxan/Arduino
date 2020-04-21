const byte botonPin = 2; //Pin al que está conectado el botón
const byte ledPin = 13; //Pin al que está conectado el led (led interno)

byte botonEstado = 0; //Variable donde se guarda el estado actual del botón

void setup()
{
	pinMode(botonPin, INPUT); //Colocar el pin 2 como una entrada
    pinMode(ledPin, OUTPUT); //Colocar el pin 13 como una salida
}

void loop()
{
	botonEstado = digitalRead(botonPin);//Leed el pin del botón, y asignarlo al estado
    if(botonEstado == 1){ //Si el estado es 1, enciende el led
        digitalWrite(ledPin, 1);
    }else //Si el estado es 0, apaga el led
    {
        digitalWrite(ledPin, 0);
    }
    
}
