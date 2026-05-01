const byte ledRojo = 2;
const byte ledVerde = 3;
int button = 8;
int state = 0;


void setup()
{
	pinMode(ledRojo, OUTPUT);
    pinMode(ledVerde, OUTPUT);
    pinMode(button, INPUT);
}

void loop()
{
	state = digitalRead(button);

    if(state == HIGH){
        digitalWrite(ledRojo, 1);
        digitalWrite(ledVerde, 0);
    }else{
        digitalWrite(ledRojo, 0);
        digitalWrite(ledVerde, 1);
    }

}
