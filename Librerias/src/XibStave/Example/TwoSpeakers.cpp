#include <Arduino.h>
#include <XibStave.h>

//Video demonstration https://youtu.be/ecUfr1Za3Rk

//Speaker pins
const uint8_t speaker1 = 8;
const uint8_t speaker2 = 9;

// BUZZER 1
uint8_t pentagrama1[][2] = {
    {NC1, N}, {NF3, N},  {END, N}, {END, N}, {NC1, N},  {NF3, N}, {NAS3, N}, {NDS4, N},
    {NGS4, N}};

// BUZZER 2
uint8_t pentagrama2[][2] = {
    {NC1, N}, {END, N},  {END, N}, {END, N}, {NC3, N},  {NF3, N}, {NAS3, N}, {NDS4, N},
    {NGS4, N}};


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
