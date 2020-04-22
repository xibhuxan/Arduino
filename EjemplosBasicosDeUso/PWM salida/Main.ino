const byte pinPWM = 3; //Pin compatible con el PWM, son aquellos que tienen un símbolo ~

void setup()
{
    pinMode(pinPWM, OUTPUT); //Colocar el pin como salida
}

void loop()
{
    analogWrite(pinPWM, 100); //Asignarle a esa salida un valor entre 0 y 255 ;0% y 100%; 0V y 5V
    //Lo interesante de esta función es sustituir el 100 por una variable que cambie con algún sensor, como un potenciómetro o LDR
}
