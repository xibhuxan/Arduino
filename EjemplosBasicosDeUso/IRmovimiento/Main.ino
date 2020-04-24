const byte IRpin = 2; //Pin de entrada del sensor

byte IRestado = 0; //Guardado de la lectura del sensor
bool movimiento = false; //Estado anterior que se considera


void setup()
{
    pinMode(IRpin, INPUT);
	Serial.begin(9600);
}

void loop()
{
	IRestado = digitalRead(IRpin); //Leer el sensor

    if(IRestado == 1){ //Si el sensor ha leido algo
        if(movimiento == false){ //Si anteriormente estaba quieto
            Serial.println("Movimiento"); //Ahora se considera que hubo movimiento
            movimiento = true; //Ahora hay movimiento
        }
    }else{ //Si no hay movimiento
        if(movimiento == true){ //Si antes hubo movimiento
            Serial.println("Quieto"); //Ahora se considera quieto
            movimiento = false; //Ahora no hay movimiento
        }
    }
}
