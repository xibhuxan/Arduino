#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "MobileLearning";
const char *password = "contra";

int usuario = 1;

void setup()
{

    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {

        delay(1000);
        Serial.print("Connecting..");
    }
    Serial.println();
    Serial.print("Conectado con IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

void loop()
{

    if (WiFi.status() == WL_CONNECTED)
    { //Check WiFi connection status

        HTTPClient http; //Declare an object of class HTTPClient

        http.begin("http://jsonplaceholder.typicode.com/users/" + String(usuario)); //Specify request destination
        int httpCode = http.GET();                                 //Send the request

        if (httpCode > 0)
        { //Check the returning code

            String payload = http.getString(); //Get the request response payload
            Serial.println(payload);           //Print the response payload
        }

        http.end(); //Close connection
    }
    
    usuario++;
    if(usuario == 11){
        usuario = 0;
    }

    delay(10000); //Send a request every 30 seconds
}