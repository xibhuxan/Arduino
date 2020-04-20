#include <NewPing.h>
 
const byte echoPin = 3;
const byte triggerPin = 2;
int MaxDistance = 200;

NewPing sonar(triggerPin, echoPin, MaxDistance);

void setup() {
  Serial.begin(9600);
}
 
void loop() {
  delay(50);                      // esperar 50ms entre pings (29ms como minimo)
  Serial.print(sonar.ping_cm()); // obtener el valor en cm (0 = fuera de rango)
  Serial.println("cm");
}
