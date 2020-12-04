#include <Arduino.h>
#include <XibStave.h>

//Video demonstration https://youtu.be/ecUfr1Za3Rk

/**
 * Optional use with buttons. And LCD.
 *
 * Required this library
 * https://github.com/Xibhu/Arduino/blob/master/Librerias/XibDebounceEdge.zip
 * If you want to see the source code
 * https://github.com/Xibhu/Arduino/tree/master/Librerias/src/XibDebounceEdge
 *
 * IMPORTANT. Set correctly the TOTAL_SPEAKERS variable inside the library, file "XibStave.h"
 */
#include <LiquidCrystal_I2C.h>
#include <XibDebounceEdge.h>

// Speaker pins
const uint8_t speaker1 = 8;
const uint8_t speaker2 = 9;

// BUZZER 1
uint8_t pentagrama1[][2] = {{NG1, NB}, {NDS4, NB},  {NDS4, NB},
                            {NDS4, NB}, {NG1, NB},  {NF3, NN},
                            {NAS3, NN}, {NDS4, NN}, {NG1, NN}};

// BUZZER 2
uint8_t pentagrama2[][2] = {{NC1, NN}, {END, NN},  {END, NN},  {END, NN}, {NC3, NN},
                            {NF3, NN}, {NAS3, NN}, {NDS4, NN}, {NGS4, NN}};

const uint8_t playButton = 2;
const uint8_t pauseButton = 3;
const uint8_t stopButton = 4;
const uint8_t loopButton = 5;
XibDebounceEdge myPlayButton(20);
XibDebounceEdge myPauseButton(20);
XibDebounceEdge myStopButton(20);
XibDebounceEdge myLoopButton(100);
bool loopState = false;

XibStave myStave;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  myStave.begin();
  myStave.addStave(*pentagrama1, sizeof(pentagrama1) / 2, speaker1);
  //myStave.addStave(*pentagrama2, sizeof(pentagrama2) / 2, speaker2);
  // myStave.play();
  // myStave.setBPM(120);
  //myStave.setSilenceDuration(50);

  pinMode(playButton, INPUT_PULLUP);
  pinMode(pauseButton, INPUT_PULLUP);
  pinMode(stopButton, INPUT_PULLUP);
  pinMode(loopButton, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("PAUSED ");
  lcd.setCursor(0, 1);
  lcd.print("LOOP OFF");
}

void loop() {

  myStave.run();

  myPlayButton.whenRisingEdge(!digitalRead(playButton), []() {
    myStave.play();
    lcd.setCursor(0, 0);
    lcd.print("PLAYING");
  });

  myPauseButton.whenRisingEdge(!digitalRead(pauseButton), []() {
    myStave.pause();
    lcd.setCursor(0, 0);
    lcd.print("PAUSED ");
  });

  myStopButton.whenRisingEdge(!digitalRead(stopButton), []() {
    myStave.stop();
    lcd.setCursor(0, 0);
    lcd.print("PAUSED ");
  });

  myLoopButton.whenRisingEdge(!digitalRead(loopButton), []() {
    loopState = !loopState;
    myStave.loop(loopState);
    if (loopState) {
      lcd.setCursor(0, 1);
      lcd.print("LOOP ON ");
    } else {
      lcd.setCursor(0, 1);
      lcd.print("LOOP OFF");
    }
  });
}
