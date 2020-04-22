const byte potenciometroPin = A0; //Pin de entrada analógica, 
//se puede utilizar el direccionamiento A0 hasta A5, o numérico como los pines digitales, en el arduino UNO de 14 a 19

int potenciometroValor = 0; //Variable donde se guarda el valor recogido del potenciómetro

void setup()
{
	pinMode(potenciometroPin, INPUT); //Configurar el pin como entrada
    Serial.begin(9600);
}

void loop()
{
	potenciometroValor = analogRead(potenciometroPin); //Recoger el valor del potenciómetro 0-1023
    Serial.println(potenciometroValor); //Enviar la variable a través del puerto serie, en 9600 baudios
    //Se puede ver con el propio programa de arduino
}
