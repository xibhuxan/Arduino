const byte microAnalog = A0;

int valorMicro = 0;
int ultimoValorMicro = 0;

void setup()
{
    Serial.begin(9600);
    ultimoValorMicro = analogRead(microAnalog);
}

void loop()
{
    valorMicro = analogRead(microAnalog);

    if (abs(valorMicro - ultimoValorMicro) > 2)
    {
        Serial.println(valorMicro);
        ultimoValorMicro = valorMicro;
    }

}
