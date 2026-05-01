const byte led = 2;
int button = 8;
int state = 0;


void setup()
{
	pinMode(led, OUTPUT);
    pinMode(button, INPUT);
}

void loop()
{
	state = digitalRead(button);

    if(state == HIGH){
        digitalWrite(led, 1);
    }else{
        digitalWrite(led, 0);
    }

}
