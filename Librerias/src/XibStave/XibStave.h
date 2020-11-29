/**
 * @brief Library to play multiple music staves
 * @author Xibhu - Carlos MR - https://github.com/xibhu (create library)
 * @author Yago-Nguyen Rodriguez Gonzalez (Initial code)
 * @author Rubén (musical help)
 * @note Telegram spanish group - 8-bit Melody Maker 2B
 * @version 0.1
 * @date 11-2020
 * @copyright GNU General Public License v3.0
 * @note This library allows you to use many staves independently, one stave per
 * speaker. To create a stave, use the variables on "Durations.h" and
 * "Pitches.h" and follows the example code.
 * @note IMPORTANT. Use a resistor between the Arduino's pin and the speaker.
 * @note IMPORTANT. Really, don't forget to change TOTAL_SPEAKERS or you will
 * get strange durations and noises.
 * @warning I don't know the speakers number limit.
 */

#ifndef XibStave_h
#define XibStave_h
#include <Arduino.h>
#include <Durations.h>
#include <Pitches.h>
#include <Tone.h>

/** IMPORTANT. Change the number according to the number of stave/speaker
       you use. */
#define TOTAL_SPEAKERS 1

class XibStave {
public:
  XibStave();
  ~XibStave();
  /**
   * @brief Continue the music.
   */
  void play();

  /**
   * @brief Pause the music.
   */
  void pause();

  /**
   * @brief Pause the music and set it to the second zero.
   */
  void stop();

  /**
   * @brief Allow you to set loop mode
   * @param activateLoop Set to true to get the loop. False to reproduce the
   * song only one time. Default:false.
   */
  void loop(bool activateLoop);

  /**
   * @brief Add a new stave to the list
   * @param stave Insert the array that act as a stave. Pointer.
   * @param staveTotalPitches Stave (array) size. Number of pitches.
   * @param pinSpeaker Pin connected to the speaker. Auto set to OUTPUT.
   */
  void addStave(uint8_t *stave, uint16_t staveTotalPitches, uint8_t pinSpeaker);

  /**
   * @brief Initial configure.
   */
  void begin();

  /**
   * @brief Reproduce the music, used inside Arduino's loop().
   */
  void run();

  /**
   * @brief Optional to set other BPM. Default:60.
   * @param newBPM Is the new BPM you want.
   */
  void setBPM(uint8_t newBPM);



private:
  /**
   * @brief Indicates if the indicated stave has finished.
   * @param indexStave Number of the finished stave you want to know.
   * @return If true, it has finished. If false, it has NOT finished.
   */
  bool staveFinished(uint8_t indexStave);

  /**
   * @brief Give you the current pitch duration.
   * @param stave Stave you want to know the current pitch durantion.
   * @return Milliseconds of the duration.
   */
  uint16_t getCurrentDurationFromStave(uint8_t stave);

  /**
   * @brief Give you the current pitch frec.
   * @param stave Stave you want to know the current pitch frec.
   */
  uint16_t getCurrentPitchFromStave(uint8_t stave);

  /**
   * @brief Allows to repeat the song if the "inLoop" variable is set to TRUE.
   */
  void repeatSong();


  bool playing = false;
  bool inLoop = false;
  bool firstPitch = true;

  uint8_t indexTotalSpeakers = 0;

  uint8_t *staves[TOTAL_SPEAKERS];
  Tone tones[TOTAL_SPEAKERS];

  uint16_t currentPitch[TOTAL_SPEAKERS];
  uint16_t totalPitches[TOTAL_SPEAKERS];
  // uint8_t indexLargestStave = 0;

  uint64_t currentTime[TOTAL_SPEAKERS];
  uint64_t prevTime[TOTAL_SPEAKERS];

  uint16_t pitchesFrec[90] = {
      31,   33,   35,   37,   39,   41,   44,   46,   49,   52,   55,   58,
      62,   65,   69,   73,   78,   82,   87,   93,   98,   104,  110,  117,
      123,  131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,
      247,  262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,
      494,  523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,
      988,  1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865,
      1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729,
      3951, 4186, 4435, 4699, 4978, 1};

  const uint16_t minute = 60000;
  uint8_t musicBPM = 60;

  uint16_t crotchetBaseTime = minute / musicBPM;

  /**
   * @see "Durations.h" to see US and UK names
   */
  uint16_t durationsForCalc[8] = {
      crotchetBaseTime,           // NEGRA
      crotchetBaseTime * 15 / 10, // NEGRA Y MEDIA
      crotchetBaseTime * 4,       // REDONDA
      crotchetBaseTime * 2,       // BLANCA
      crotchetBaseTime / 2,       // CORCHEA
      crotchetBaseTime / 3,       // TRESILLO
      crotchetBaseTime / 4,       // SEMICORCHEA
      crotchetBaseTime / 8        // FUSA
  };

  uint16_t durations[8];
};

#endif