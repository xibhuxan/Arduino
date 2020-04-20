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
 
    byte num = readButtons();
    
    Serial.println(num);



    switch (num)
    {

    case 1: enviarDato(0xc8, 0x76);
            enviarDato(0xca, 0x3f);
            enviarDato(0xcc, 0x38);
            enviarDato(0xce, 0x77);

        break;
        
    case 2: enviarDato(0xc8, 0xbf);
            enviarDato(0xca, 0x3e);
            enviarDato(0xcc, 0x79);
            

        break;
    case 4: enviarDato(0xc8, 0x07);
            enviarDato(0xca, 0x77);
            enviarDato(0xcc, 0x38);
            enviarDato(0xce, 0xd3);
            
        break;

  default:
    reset();
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

void enviarDato(byte display, byte valor){
    digitalWrite(strobe, LOW);
    shiftOut(data, clock, LSBFIRST, display); // 1st digit
    shiftOut(data, clock, LSBFIRST, valor);
    digitalWrite(strobe, HIGH);
}