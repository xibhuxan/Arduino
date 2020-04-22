const byte potenciometroPin = A0; //Pin de entrada analógica, 
//se puede utilizar el direccionamiento A0 hasta A5, o numérico como los pines digitales, en el arduino UNO de 14 a 19
const byte pwmPin = 3; //Pin pwm para darle una utilidad al valor recogido del potenciómetro

int potenciometroValor = 0; //Variable donde se guarda el valor recogido del potenciómetro

void setup()
{
	pinMode(potenciometroPin, INPUT); //Configurar el pin como entrada
    pinMode(pwmPin, OUTPUT); //Configurar el pin como salida
}

void loop()
{
	potenciometroValor = analogRead(potenciometroPin); //Recoger el valor del potenciómetro 0-1023
    analogWrite(pwmPin, potenciometroValor/4); //Colocar el valor del potenciómetro en el pin PWM, 
    //se divide entre 4 porque el pwm va hasta 255, de esa manera se tiene todo el recorrido del potenciometro como 0-255
}
