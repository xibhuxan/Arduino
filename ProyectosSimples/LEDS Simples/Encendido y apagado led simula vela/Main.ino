const byte led = 3;

int brightRandom = 0;
int timeRandom = 0;

void setup()
{
	randomSeed(0); //Inicializar los valores random
    pinMode(3, OUTPUT);
}

void loop()
{
	
    brightRandom = random(100,255); //Valor aleatorio entre 100 y 255 para el PWM de salida al led
    analogWrite(led, brightRandom);
    timeRandom = random(50,150);//Valor aleatorio entre 50 y 150 de milisegundos para que se repita el bucle
    delay(timeRandom);

}
