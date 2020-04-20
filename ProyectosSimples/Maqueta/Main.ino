#include <Servo.h>          // Incluir la librería Servo
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo servo1;               // Crear un objeto tipo Servo llamado servo1

int angulo = 0 ;
int Eje_X = A1 ;
int Eje_Y = A2 ;

#define I2C_ADDR 0x27 //Define I2C Address where the PCF8574A is


//define variables for the LM35 temperature sensor

float temp; //Define the temp float variable

float tempf; //Define the Fahrenheit float variable

int sensort = A0; // sensor middle pin on analog pin 0

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);


const int buzzer = 4; 
const int sensor = 3;
int state = 1; // 0 close - 1 open wwitch

int Led = 8 ;// define LED Interface
int Shock = 9; // define the vibration sensor interface
int val; // define numeric variables val

void setup()
{

pinMode (Led, OUTPUT) ; // define LED as output interface
  pinMode (Shock, INPUT) ; // output interface defines vibration sensor
  
  lcd.init(); //Define the LCD as 16 column by 2 rows

//Switch on the backlight

lcd.backlight();

lcd.setCursor(0,0); //goto first column (column 0) and first line (Line 0)

lcd.print("Temp C = "); //Print at cursor Location

lcd.setCursor(0,1); //goto first column (column 0) and second line (line 1)

lcd.print("Temp F = "); //Print at cursor location

  Serial.begin (9600);
  
servo1.attach(6) ;  // Conectar servo1 al pin 6

    }

void loop()
    {


val = digitalRead (Shock) ; // read digital interface is assigned a value of 3 val
Serial.println(val);
  if (val == HIGH) // When the shock sensor detects a signal, LED flashes
  {
    digitalWrite (Led, LOW);
  }
  else
  {
    digitalWrite (Led, HIGH);
  }

angulo  = map(analogRead(Eje_X), 0, 1024, 0, 180);
servo1.write(angulo);


temp = analogRead(sensort); //assigning the analog output to temp

temp = temp * 0.48828125; //converting volts to degrees celsius ----- 0.48828125 = [(5V*1000)/1024]10 tempf = (temp * 1.8)+32; //Convering from celsius to fahreneit
tempf = temp + 33.8;
lcd.setCursor(8,0); //move the cursor to position 8 on row 1

lcd.print(temp); //print the temperature in Celsius

lcd.setCursor(8,1); //move the cursor to position 8 on row 2

lcd.print(tempf); //print the temperature in Fahrenheit


delay(500); //wait 5 seconds
state = digitalRead(sensor);
  
  if (state == LOW){
    tone(buzzer, 400);
  }
  else{
    noTone(buzzer);
  }
  delay(100);
  

} 
   