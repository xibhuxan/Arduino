const int strobe = 7;
const int clock = 9;
const int data = 8;
 
void sendCommand(uint8_t value)
{
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, value);
  digitalWrite(strobe, HIGH);
}
 
void reset()
{
  sendCommand(0x40); // set auto increment mode
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0xc0);   // set starting address to 0
  for(uint8_t i = 0; i < 16; i++)
  {
    shiftOut(data, clock, LSBFIRST, 0x00);
  }
  digitalWrite(strobe, HIGH);
}
 
void setup()
{
    pinMode(strobe, OUTPUT);
    pinMode(clock, OUTPUT);
    pinMode(data, OUTPUT);
    

    Serial.begin(9600);

    sendCommand(0x8f);  // activate and set brightness to max
    reset();
}

void loop(){
    sendCommand(0x44);  // set single address
 /*
    digitalWrite(strobe, LOW);
    shiftOut(data, clock, LSBFIRST, 0xc0); // 1st digit
    shiftOut(data, clock, LSBFIRST, 0x0a);
    digitalWrite(strobe, HIGH);
    
    digitalWrite(strobe, LOW);
    shiftOut(data, clock, LSBFIRST, 0xc5); // 3rd LED
    shiftOut(data, clock, LSBFIRST, 0x01);
    digitalWrite(strobe, HIGH);
    
    digitalWrite(strobe, LOW);
    shiftOut(data, clock, LSBFIRST, 0xcb); // 6rd LED
    shiftOut(data, clock, LSBFIRST, 0x01);
    digitalWrite(strobe, HIGH);
    
    digitalWrite(strobe, LOW);
    shiftOut(data, clock, LSBFIRST, 0xce); // last digit
    shiftOut(data, clock, LSBFIRST, 0xff);
    digitalWrite(strobe, HIGH);
*/
    byte num = readButtons();
    
    Serial.println(num);

    switch (num)
    {
    case 0: escribirPantalla(0x3f);

        break;
    case 1: escribirPantalla(0x06);

        break;
    case 2: escribirPantalla(0x5b);

        break;
    case 4: escribirPantalla(0x4f);

        break;
    case 8: escribirPantalla(0x66);

        break;
    case 16: escribirPantalla(0x6d);

        break;
    case 32: escribirPantalla(0x7d);

        break;
    case 64: escribirPantalla(0x07);

        break;
    case 128: escribirPantalla(0x7f);

        break;
   
    }

}

uint8_t readButtons(void)
{
  uint8_t buttons = 0;
  digitalWrite(strobe, LOW);
  shiftOut(data, clock, LSBFIRST, 0x42);

  pinMode(data, INPUT);

  for (uint8_t i = 0; i < 4; i++)
  {
    uint8_t v = shiftIn(data, clock, LSBFIRST) << i;
    buttons |= v;
  }

  pinMode(data, OUTPUT);
  digitalWrite(strobe, HIGH);
  return buttons;
}



void escribirPantalla(byte num){
    digitalWrite(strobe, LOW);
    shiftOut(data, clock, LSBFIRST, 0xc0); // 1st digit
    shiftOut(data, clock, LSBFIRST, num);
    digitalWrite(strobe, HIGH);
}