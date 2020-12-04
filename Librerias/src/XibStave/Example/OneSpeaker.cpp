#include <Arduino.h>
#include <XibStave.h>

//Video demonstration https://youtu.be/ecUfr1Za3Rk

//Speaker pins
const uint8_t speaker1 = 8;

// BUZZER 1
uint8_t pentagrama1[][2] = {
    {NC1, NN}, {NF3, NN},  {END, NN}, {END, NN}, {NC1, NN},  {NF3, NN}, {NAS3, NN}, {NDS4, NN},
    {NGS4, NN}};



XibStave myStave;

void setup() {
  myStave.begin();
  myStave.addStave(*pentagrama1, sizeof(pentagrama1)/2, speaker1);
  myStave.play();
  //myStave.setSilenceDuration(50);

}

void loop() {

  myStave.run();

}
