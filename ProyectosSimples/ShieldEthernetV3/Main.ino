#include "IRLremote.h"
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
const byte TAMPIN = 5;
const byte pinDigital[TAMPIN] = {5, 6, 7, 8, 9};
bool valDigital[TAMPIN] = {false, false, false, false, false};
const byte pinPwm = 3;
int valPwm = 0;

/**
 * Variable de apertura de ficheros.
*/
File fichero;

/*
    Variables de mando
*/

const int interruptIR = 0;
uint8_t IRProtocol = 0;
uint16_t IRAddress = 0;
uint32_t IRCommand = 0;

/*
    Variables de ldr
*/

const byte LDR = A0;
int valorLDR = 0;
bool activarLDR = false;

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

    IRLbegin<IR_ALL>(interruptIR);
}

void loop()
{

    if (activarLDR)
    {

        valorLDR = analogRead(LDR);
        valorLDR = map(valorLDR, 250, 750, 0, 6);

        switch (valorLDR)
        {
        case 0:
            LDRSwitch(1,1,1,1,1);
            break;
        case 1:
            LDRSwitch(1,1,1,1,0);
            break;
        case 2:
            LDRSwitch(1,1,1,0,0);
            break;
        case 3:
            LDRSwitch(1,1,0,0,0);
            break;
        case 4:
            LDRSwitch(1,0,0,0,0);
            break;
        case 5:
            LDRSwitch(0,0,0,0,0);
            break;
        default:
            break;
        }
        delay(50);
    }

    uint8_t oldSREG = SREG; // Parar las interrupciones
    cli();

    if (IRProtocol) // Si reconoce el protocolo
    {
        IRProtocol = 0;
        Serial.println(IRCommand, HEX);
        switch (IRCommand)
        {
        case 0x30CF: //1
            valDigital[0] = !valDigital[0];
            digitalWrite(pinDigital[0], valDigital[0]);
            break;

        case 0x52AD: //9
            valDigital[1] = !valDigital[1];
            digitalWrite(pinDigital[1], valDigital[1]);
            break;

        case 0xA857: //+
            valDigital[2] = !valDigital[2];
            digitalWrite(pinDigital[2], valDigital[2]);
            break;

        case 0xB04F: //200+
            activarLDR = !activarLDR;
            break;

        default:
            break;
        }
    }
    SREG = oldSREG;

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

void IREvent(uint8_t protocol, uint16_t address, uint32_t command)
{
    IRProtocol = protocol;
    IRAddress = address;
    IRCommand = command;
}

void LDRSwitch(int a, int b, int c, int d, int e)
{
    digitalWrite(pinDigital[0], a);
    digitalWrite(pinDigital[1], b);
    digitalWrite(pinDigital[2], c);
    digitalWrite(pinDigital[3], d);
    digitalWrite(pinDigital[4], e);
}