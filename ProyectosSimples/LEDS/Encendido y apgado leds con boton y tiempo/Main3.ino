const byte ledRojo = 2;
const byte ledVerde = 3;
const byte ledAmarillo = 4;

const byte button = 8;

int buttonState = 0;

void setup()
{
	pinMode(ledRojo, OUTPUT);
    pinMode(ledVerde, OUTPUT);
    pinMode(ledAmarillo, OUTPUT);
    pinMode(button, INPUT);
    digitalWrite(ledRojo, 1);
}

void loop()
{
	
    buttonState = digitalRead(button);
    if(buttonState == HIGH){
        digitalWrite(ledRojo,0);
        digitalWrite(ledAmarillo,1);
        delay(1000);
        digitalWrite(ledAmarillo,0);
        digitalWrite(ledVerde,1);
        delay(5000);
        digitalWrite(ledRojo,1);
        digitalWrite(ledVerde,0);
    }

}
