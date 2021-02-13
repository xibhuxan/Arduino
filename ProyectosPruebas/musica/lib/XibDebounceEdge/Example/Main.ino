#include <XibDebounceEdge.h>

const int buttonPin = 2; 
const int ledPin = 13;   
const int ledPin2 = 12; 
const int ledPin3 = 11; 

//Increase the "20" (milliseconds) if you still get false readings from the button, or 0 if you dont need debounce
XibDebounceEdge myDebounce1(20);
XibDebounceEdge myDebounce2(20);
XibDebounceEdge myDebounce3(20);
XibDebounceEdge myDebounce4(20);

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
//You can use this set of functions

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
  
  //or this set functions, they are the same, but in one set you can put code inside the parameter, and in the other set, you receive a bool (delete comments symbols)

  /*
  if (myDebounce1.whenActive(reading))
  {
    digitalWrite(ledPin, 1);
  }
  if (myDebounce2.whenDeactive(reading))
  {
    digitalWrite(ledPin, 0);
  }
  if (myDebounce3.whenRisingEdge(reading))
  {
    digitalWrite(ledPin2, led2State = !led2State);
  }
  if (myDebounce4.whenFallingEdge(reading))
  {
    digitalWrite(ledPin3, led3State = !led3State);
  }
  */
  
}
