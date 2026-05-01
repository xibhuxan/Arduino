const byte ledRojo = 2;
const byte ledVerde = 3;
int ledAmarillo = 4;
int buttonOne = 8;

int stateButtonOne = 0;

int modoParpadeo = 0;
int duracion = 1000;

bool block = false;

void setup()
{
	pinMode(ledRojo, OUTPUT);
    pinMode(ledVerde, OUTPUT);
    pinMode(ledAmarillo, OUTPUT);
    pinMode(buttonOne, INPUT);
    Serial.begin(9600);
}

void loop()
{
    Serial.println(modoParpadeo);
    onLed(1,0,0,0,duracion);
    onLed(0,1,0,0,duracion);
    onLed(0,0,1,0,duracion);

    onLed(0,0,1,1,duracion);
    onLed(0,1,0,1,duracion);
    onLed(1,0,0,1,duracion);
}


void onLed(int v, int a, int r, int modParpa, int dur){

    for(int i = 0; i < dur && modParpa == modoParpadeo; i++){
        comprobarButton();
        digitalWrite(ledVerde, v);
        digitalWrite(ledAmarillo, a);
        digitalWrite(ledRojo, r);
        delay(1);
    }

}

void comprobarButton(){
    stateButtonOne = digitalRead(buttonOne);
    
    if(stateButtonOne == HIGH && !block){
        block = true;
        if(modoParpadeo == 0){
            modoParpadeo = 1;
        }else{
            modoParpadeo = 0;
        }
    }
    if(stateButtonOne == LOW)
        block = false;
}