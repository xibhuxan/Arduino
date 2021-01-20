//Códdigo fuente 2 para la placa2 de Arduino

int antes = 0;
int recibido = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600); 
}

void loop(){
  //Para comprobar si se ha recibido algo desde el otro ARduino
  if(Serial.available() > 0) {
    recibido = Serial.read()
    if (recibido > antes) {   
      //Si el número generado por el contador del otro Arduino que se envia a este es mayor que el anterior recibido, parpadean los LEDs de esta placa
      antes = recibido;
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(2, LOW);
      digitalWrite(7, HIGH);
      delay(500);
      digitalWrite(7, LOW);
    }
  }
}
