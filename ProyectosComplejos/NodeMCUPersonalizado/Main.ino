#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Web.h>

const char *ssid = "MobileLearning";
const char *password = "CONTRASEÑA";

WiFiServer server(80);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Wire.begin(D2, D1);

    lcd.init();
    lcd.backlight();

    Serial.begin(115200);
    delay(1500);

    // prepare GPIO2
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    // Start the server
    server.begin();
    Serial.println("Server started");

    // Print the IP address
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
    lcd.setCursor(0, 0);
    lcd.print(WiFi.localIP());
}

void loop()
{

    WiFiClient client = server.available();
    if (!client)
    {
        return;
    }

    Serial.println("new client");

    while (!client.available())
    {
        delay(1);
    }

    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();
   
    String ipString = WiFi.localIP().toString();


    Web miWeb("Servidor NodeMCU");
    miWeb.addItemBody("<h1>Servidor WEB NodeMCU</h1>");
    miWeb.addItemBody("<form action='http://" + ipString +"/on'><input type='submit' value='Encender' /></form>");
    miWeb.addItemBody("<form action='http://" + ipString +"/off'><input type='submit' value='Apagar' /></form>");


    // Match the request
    int val;
    Serial.println(req);

    if (req.indexOf("/on") != -1)
    {
        val = 0;
        lcd.setCursor(0, 1);
        lcd.print("Led endendido  O");
    }
    else if (req.indexOf("/off") != -1)
    {
        val = 1;
        lcd.setCursor(0, 1);
        lcd.print("Led apagado    X");
    }

    // Set GPIO2 according to the request
    digitalWrite(2, val);

    client.flush();

    // Prepare the response
    String s;
    s += (val) ? "<p style='color:red';>Led apagado</p>" : "<p style='color:green';>Led encendido</p>";
    miWeb.addItemBody("<h1>" + s + "</h1>");

    // Send the response to the client
    client.print(miWeb.getWeb());
    delay(1);
    Serial.println("Client disonnected");
}
