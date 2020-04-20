#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

/**
 * Variables relacionadas con Ethernet
 * mac, identificador de la tarjeta de red.
 * ip, direccion ip que tendrá el shield.
 * server, puerto por el que escuchará las peticiones.
 * miIp, string auxiliar para tener la ip.
 * 
*/
byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 230);
EthernetServer server(80);
String miIp = "";

/**
 * Variables de pines de salida.
 * TAMPIN, tamaño de la cantidad de salidas digitales.
 * pinDigital, pines concretos que se utilizan para las salidas digitales.
 * valDigital, valor de esos pines digitales.
 * pinPwm, pin que actuará como pwm.
 * valPwm, valor del pin pwm.
*/
const byte TAMPIN = 6;
const byte pinDigital[TAMPIN] = {2, 5, 6, 7, 8, 9};
bool valDigital[TAMPIN] = {false, false, false, false, false, false};
const byte pinPwm = 3;
int valPwm = 0;

/**
 * Variable de apertura de ficheros.
*/
File fichero;

void setup()
{
    //Abrir comunicación serie con el usb si hiciera falta.
    Serial.begin(9600);

    //Asignación de los pines como salidas.
    for (int i = 0; i < TAMPIN; i++)
    {
        pinMode(pinDigital[i], OUTPUT);
    }
    pinMode(pinPwm, OUTPUT);

    //Colocación de los pines esclavos de dispositivo Ethernet y SD.
    Ethernet.init(10);
    if (!SD.begin(4))
    {
        Serial.println("Error con la SD!");
        while (1)
            ;
    }
    else
    {
        Serial.println("Funciona SD");
    }

    Serial.println("Shield conectado.");

    //Encender el chip con una dirección mac e ip.
    Ethernet.begin(mac, ip);

    //Si el shield está mal conectado salta error.
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println("Tienes el shield de Ethernet mal conectado.");
        while (true)
        {
            delay(1);
        }
    }
    //Si el cable está mal conectado salta error, nunca ha saltado.
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("El cable de red no está conectado.");
    }

    //Comenzar el servidor.
    server.begin();
    Serial.print("Servidor en IP: ");

    //Guardar la ip en un string por si fuera necesario utilizarlo.
    miIp = String(Ethernet.localIP()[0]) + "." +
           String(Ethernet.localIP()[1]) + "." +
           String(Ethernet.localIP()[2]) + "." +
           String(Ethernet.localIP()[3]);

    Serial.println(miIp);
}

void loop()
{
    //Si hay un cliente disponible para conectarse, se guarda.
    EthernetClient client = server.available();

    if (client)
    {
        //Se lee hasta donde empieza HTML de la primera linea.
        String s = client.readStringUntil('H'); //client.readStringUntil('\r'); /*por si se necesita la linea entera*/

        //Se comprueba si se ha recibido un comando de conmutación de pin, y se actúa.
        for (int i = 0; i < TAMPIN; i++)
        {

            if (s.indexOf("/pin" + String(pinDigital[i])) != -1)
            {
                valDigital[i] = !valDigital[i];
            }
            digitalWrite(pinDigital[i], valDigital[i]);
        }

        //Se comprueba si se ha recibido un comando de pwm y se actúa.
        int index = s.indexOf("pwm");

        if (index != -1)
        {
            valPwm = s.substring(index + 4, index + 7).toInt();
            analogWrite(pinPwm, valPwm);
        }

        //Se manda al cliente que la operación está correcta.
        client.println("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");

        //Se accede al archivo que contiene la página web, se le da al cliente y se cierra el archivo.
        fichero = SD.open("index.txt");
        if (fichero.available())
        {
            while (fichero.available())
                client.write(fichero.read());
        }
        fichero.close();

        //Se envía al cliente el estado de las salidas digitales.
        for (int i = 0; i < TAMPIN; i++)
        {
            client.print("<br><br><span>Pin " + String(pinDigital[i]) + ": " + String(valDigital[i]) + "</span>");
        }

        //Se envía al cliente el valor del pwm utilizado.
        client.print("<br><br><span>PinPwm " + String(pinPwm) + ": " + String(valPwm) + "</span>");

        client.stop();
    }
}
