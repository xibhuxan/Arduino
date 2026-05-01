int valor = 0;                 // Variable que contiene el valor a sacar por el terminal analógico
const byte motor = 10;         // Motor conectado al PIN 10
const byte potenciometro = A0; // Se define la entrada analógica

void setup() {} // No es necesario

void loop()
{
    valor = analogRead(potenciometro); // Se lee el valor de la entrada analógica y se asigna a 'valor'
    analogWrite(motor, valor);         // Se manda a la salida analógica 0 el valor leído
    delay(30);                         // Espera 30 ms para que el efecto sea visible
}
