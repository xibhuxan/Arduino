#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//SERVO
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  80
#define SERVOMAX  450

uint8_t servonum = 0;


//PANTALLA
LiquidCrystal_I2C lcd(0x26, 16, 2);

//STICK
int pinPotX = A0;
int pinPotY = A1;
int valorPotX = 0;
int valorPotY = 0;

int pinButton = 6;
int stateButton = 0;


void setup()
{
    lcd.init();
    lcd.backlight();

    pinMode(pinButton, INPUT_PULLUP);

    pwm.begin();
    pwm.setPWMFreq(50);

    lcd.setCursor(0,0);
    lcd.print("Motor numero: ");
    lcd.print(servonum);
}

void loop()
{

    if(!digitalRead(pinButton)){
        servonum += 2;
        servonum = servonum % 4;

        lcd.setCursor(0,0);
        lcd.print("Motor numero: ");
        lcd.print(servonum);

        delay(250);
    }

    controlServo(pinPotX, valorPotX,servonum);
    controlServo(pinPotY, valorPotY,servonum+1);
    
}

void controlServo(int pin, int valor, int numServo){
    valor = analogRead(pin);
    valor = map(valor, 0, 1023, SERVOMIN, SERVOMAX);
    pwm.setPWM(numServo, 0, valor);
}