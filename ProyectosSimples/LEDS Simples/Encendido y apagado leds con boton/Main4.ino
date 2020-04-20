const byte ledRojo = 2;
const byte ledVerde = 3;
int buttonOne = 8;
int buttonTwo = 9;

int stateButtonOne = 0;
int stateButtonTwo = 0;

void setup()
{
	pinMode(ledRojo, OUTPUT);
    pinMode(ledVerde, OUTPUT);
    pinMode(buttonOne, INPUT);
    pinMode(buttonTwo, INPUT);
}

void loop()
{
	stateButtonOne = digitalRead(buttonOne);
    stateButtonTwo = digitalRead(buttonTwo);

    if(stateButtonOne == LOW || stateButtonTwo == LOW){
        if(stateButtonOne == HIGH){
            digitalWrite(ledRojo, 1);
            digitalWrite(ledVerde, 0);
        }
        if(stateButtonTwo == HIGH){
            digitalWrite(ledRojo, 0);
            digitalWrite(ledVerde, 1);
        }
    }

    

}
