#include <nRF24L01.h>
#include <printf.h>
#include <RF24_config.h>
#include <RF24.h>
#include <SPI.h>

/* Crear un objeto RF24 al que llamaremos “radio”. 
Los dos argumentos que se utilizan en la funcion 
son los numeros de pin que vamos a usar para CS y CE. */
RF24 radio(7, 8); // CE, CSN

/* Creamos una matriz de bytes que represente la 
direccion con la que se reconoceran entre si los 
dos modulos. Podemos cambiar el valor de esta 
direccion a cualquier conjunto de 5 letras y/o 
numeros. Esta direccion permite elegir con que 
receptor vamos a comunicarnos. En nuestro caso, 
usaremos la misma direccion tanto en el receptor 
como en el transmisor. */
const byte identificacion[6] = "00001";

void setup()
{
  /* En la seccion de configuracion debemos inicializar 
el objeto “radio” */
  radio.begin();

  /* Mediante la funcion radio.openWritingPipe(), 
establecer la direccion del receptor al que 
enviaremos los datos. En este ejemplo, la cadena 
de 5 caracteres que hemos configurado. */
  radio.openWritingPipe(identificacion);

  /* Configuramos el nivel del amplificador de potencia,
usando la funcion radio.setPALevel(). Mientras 
estemos a este nivel de prueba, es decir prototipos 
sobre la mesa de trabajo, lo establecemos al minimo, 
ya que los modulos estaran cerca el uno del otro. 
Si se utiliza un nivel mas alto, se recomienda 
utilizar capacitores de filtro entre las entradas 
GND y 3,3 V de los mdulos para que su voltaje se 
mantenga más estable durante el funcionamiento. */
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);

  /* La función radio.stopListening() cumple la de establecer al módulo como transmisor. */
  radio.stopListening();
}

void loop()
{
  /* Creamos una matriz de caracteres a la que 
asignamos el mensaje "Hola mundo" o cualquiera 
que usted desee enviar. */
  const char texto[] = "Hola Mundo";

  /* Usando la funcion radio.write() se envía el 
mensaje al receptor. El primer argumento es la 
variable que deseamos enviar. */
  radio.write(&texto, sizeof(texto));
  /* El simbolo “&” delante del nombre de la variable 
establece un indicador que apunta a la variable 
que contiene los datos que queremos enviar y, con 
el segundo argumento, establecemos la cantidad 
de bytes que se van a usar de esa variable. En 
este caso, la funcion sizeof() nos devuelve la 
cantidad total de los bytes de la cadena "texto". */

  delay(500); // Un segundo (1000 milisegundos) de espera entre envío y envío
}