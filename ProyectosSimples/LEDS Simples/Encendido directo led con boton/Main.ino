const byte led = 2;    // Pin para el led
const byte button = 3; // pin para el boton

byte buttonState = 0; // Para guardar el estado del botón

void setup()
{
    pinMode(led, OUTPUT);          // El pin del led como salida
    pinMode(button, INPUT_PULLUP); // El pin del botón como entrada en estado PULLUP. NO SE UTILIZA RESISTENCIA, del pin va al botón, y del botón a tierra directamente.
}

void loop()
{
    buttonState = !digitalRead(button); // Se lee el pin, pero como está en PULLUP, se lee al contrario, por eso se utiliza el símbolo !, que es la negación
    digitalWrite(led, buttonState);
}
