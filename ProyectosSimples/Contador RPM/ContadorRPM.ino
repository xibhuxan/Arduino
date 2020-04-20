// Contador de RPM  by: http://elprofegarcia.com
// Conexion de la entrada de la interrupcion 0  por el PIN 2
// Configurar el monitor serial a 57600 Baudios para visualizar los RPM
// Tienda para comprar Materiales http://dinastiatecnologica.com

volatile int contador = 0;   // Variable entera que se almacena en la RAM del Micro
 
void setup() {
  Serial.begin(57600);
  attachInterrupt(0,interrupcion0,RISING);  // Interrupcion 0 (pin2) 
}                                          // LOW, CHANGE, RISING, FALLING
 
void loop() {
  delay(999);               // retardo de casi 1 segundo
  Serial.print(contador*60); // Como son dos interrupciones por vuelta (contador * (60/2)) El numero 2 depende del numero aspas de la helice del motor en prueba
  Serial.println(" RPM");
  contador = 0;
}
 
void interrupcion0()    // Funcion que se ejecuta durante cada interrupion
{
  contador++;           // Se incrementa en uno el contador
}


//https://create.arduino.cc/editor/ProfeGarcia/ec7844e0-f33e-4a09-b636-910d9fadd8c2/preview
