//Pines que se van a utilizar
const byte ledG = 2;
const byte ledR = 3;
const byte ledY = 4;

int timeSwitch = 200;

void setup()
{
	pinMode(ledG, OUTPUT);
    pinMode(ledR, OUTPUT);
    pinMode(ledY, OUTPUT);
}

void loop()
{
	digitalWrite(ledY, 0);
    digitalWrite(ledG, 1);
    delay(timeSwitch);

    digitalWrite(ledG, 0);
    digitalWrite(ledR, 1);
    delay(timeSwitch);    
    
    digitalWrite(ledR, 0);
    digitalWrite(ledY, 1);
    delay(timeSwitch);
}
