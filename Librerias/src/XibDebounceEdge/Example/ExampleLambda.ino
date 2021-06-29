#include <XibDebounceEdge.h>

const uint8_t buttonPin = 2;

const uint8_t ledPin1 = 13;
const uint8_t ledPin2 = 12;
const uint8_t ledPin3 = 11;

//Increase the "20" (milliseconds) if you still get false readings from the button, or 0 if you dont need debounce
uint16_t debounceTime = 20;

XibDebounceEdge myDebounce1(debounceTime);
XibDebounceEdge myDebounce2(debounceTime);
XibDebounceEdge myDebounce3(debounceTime);
XibDebounceEdge myDebounce4(debounceTime);

bool led2State;
bool led3State;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop()
{
  //Read from the pin that you have the button (or sensor in general)
  //The exclamation "!" it's needed because i'm using the internal PULLUP, so the signal it's inverted (If I press the button, the digitalRead give me a FALSE, with "!" I get TRUE)
  bool reading = !digitalRead(buttonPin);

  //There are two parameters, the variable you want to watch and the function you want to execute. In this case it's a lambda funcition, you write it directly (with its symbols), without a name.

  //LIBRARY FUNCTIONS

  //while the input it's on (true), the function "whenActive" do the function forever, until change to false
  myDebounce1.whenActive(reading, []() {
    //Do stuff here

    //Turn on led1
    digitalWrite(ledPin1, 1);
  });

  //while the input it's off (false), the function "whenDeactive" do the function forever, until change to true
  myDebounce2.whenDeactive(reading, []() {
    //Turn off led1
    digitalWrite(ledPin1, 0);
  });

  //Only in the rising edge the function works (one time per rising edge)
  myDebounce3.whenRisingEdge(reading, []() {
    //Change state led2. Assign the same var with "!" save the contrary value. And then use its value. (First change, second use)
    led2State = !led2State;
    digitalWrite(ledPin2, led2State);
  });

  //Only in the falling edge the function works (one time per falling edge)
  myDebounce4.whenFallingEdge(reading, []() {
    //Change state led3. Assign the same var with "!" save the contrary value. And then use its value. (First change, second use)
    led3State = !led3State;
    digitalWrite(ledPin3, led3State);
  });
}
