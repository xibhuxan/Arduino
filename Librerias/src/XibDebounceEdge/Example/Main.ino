#include <XibDebounceEdge.h>

const int buttonPin = 2; 
const int ledPin = 13;   
const int ledPin2 = 12; 
const int ledPin3 = 11; 

//Increase the "20" (milliseconds) if you still get false readings from the button
XibDebounce myDebounce1(20);
XibDebounce myDebounce2(20);
XibDebounce myDebounce3(20);
XibDebounce myDebounce4(20);

bool led2State;
bool led3State;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop()
{

  bool reading = !digitalRead(buttonPin); //Read from the pin that have the button

//while the input it's on, the function "whenActive" do the personal function
  myDebounce1.whenActive(reading, []() {
    digitalWrite(ledPin, 1);
  });
  
//while the input it's off, the function "whenDeactive" do the personal function
  myDebounce2.whenDeactive(reading, []() {
    digitalWrite(ledPin, 0);
  });
  
//Only in the rising edge, the personal function works (one time per rising edge)
  myDebounce3.whenRisingEdge(reading, []() {
    digitalWrite(ledPin2, led2State = !led2State);
  });
  
//Only in the falling edge, the personal function works (one time per falling edge)
  myDebounce4.whenFallingEdge(reading, []() {
    digitalWrite(ledPin3, led3State = !led3State);
  });
  
}
