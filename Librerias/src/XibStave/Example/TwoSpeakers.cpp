#include <Arduino.h>
#include <XibStave.h>

//Video demonstration https://youtu.be/ecUfr1Za3Rk

//Speaker pins
const uint8_t speaker1 = 8;
const uint8_t speaker2 = 9;

// BUZZER 1
uint8_t pentagrama1[][2] = {
    {NC1, NN}, {NF3, NN},  {END, NN}, {END, NN}, {NC1, NN},  {NF3, NN}, {NAS3, NN}, {NDS4, NN},
    {NGS4, NN}};

// BUZZER 2
uint8_t pentagrama2[][2] = {
    {NC1, NN}, {END, NN},  {END, NN}, {END, NN}, {NC3, NN},  {NF3, NN}, {NAS3, NN}, {NDS4, NN},
    {NGS4, NN}};


XibStave myStave;

void setup() {
  myStave.begin();
  myStave.addStave(*pentagrama1, sizeof(pentagrama1)/2, speaker1);
  myStave.addStave(*pentagrama2, sizeof(pentagrama2)/2, speaker2);
  myStave.play();

}

void loop() {

  myStave.run();

}
