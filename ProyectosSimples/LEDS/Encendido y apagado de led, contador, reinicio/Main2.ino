const byte led = 2;

const byte button = 8;

int buttonState = 0;

bool block = false;
int contador = 0;

void setup()
{
	pinMode(led, OUTPUT);
    pinMode(button, INPUT);
    Serial.begin(9600);
}

void loop()
{
	
    buttonState = digitalRead(button);

    if(buttonState == HIGH && !block){
        Serial.println(++contador);
        if(contador%4 == 0)
            digitalWrite(led,1);
        block = true;
    }
    if(buttonState == LOW){
        block = false;
        digitalWrite(led,0);
    }

}
