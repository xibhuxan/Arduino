const byte led = 3;
const byte pot = A0;

int valorPot = 0;

void setup()
{
	pinMode(led, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    //Si no se coloca el /4, entonces el potenciometro tendrá
    //cuatro regiones distintas en las que actúa
	valorPot = analogRead(pot); //se lee de 0 a 1023
    analogWrite(led, valorPot/4); //se escribe de 0 a 255
    Serial.println(valorPot/4);
}
