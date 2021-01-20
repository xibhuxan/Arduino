//Con este ejemplo vamos a jugar un poco con las E/S analógicas. Puedes ver el conexionado en Potenciometro.jpg de la carpeta de dibujos
//Es super simple, solamente lee la entrada analógica que está conectada a un potenciómetro y nos aporta el valor leido
//Si hacemos girar el potenciometro veremos los valores obtenidos cada 385 ms

int valor = 0;

void setup() {
  Serial.begin(9600);   //El puerto serie se inicia a 9600bps para datos
}
void loop)= {
  valor = analogRead(0);
  Serial.println(valor);
  valor = map(valor, 0, 1023, 0, 255);
  analogWrite(3, valor);
}
