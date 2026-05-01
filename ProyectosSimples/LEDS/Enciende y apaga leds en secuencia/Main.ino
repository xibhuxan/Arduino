const byte leds[] = {2,3,4,5,6,7};
int ledsSize = 6;

void setup()
{
	for(int i = 0; i < ledsSize; i++){
        pinMode(leds[i], OUTPUT);
    }
    Serial.begin(9600);
}

void loop()
{

    secuenciaLedsIncremental(100);
	secuenciaLedsDecremental(100);
}

void secuenciaLedsIncremental(int espera){

    for(int i = 0; i < ledsSize; i++){
        
        digitalWrite(leds[i], 1);
        delay(espera);
        digitalWrite(leds[i], 0);

    }

}
void secuenciaLedsDecremental(int espera){

    for(int i = ledsSize-1; i >= 0; i--){
        
        digitalWrite(leds[i], 1);
        delay(espera);
        digitalWrite(leds[i], 0);

    }

}
