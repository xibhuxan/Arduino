#include <XibStave.h>

XibStave::XibStave()
{
}

XibStave::~XibStave()
{
}

void XibStave::play ()
{
  playing = true;
}

void XibStave::pause ()
{
  playing = false;

  for ( uint8_t i = 0; i < TOTAL_SPEAKERS; i++ )
  {
    tones[i].stop();
  }
}

void XibStave::stop ()
{
  pause();
  for ( uint8_t i = 0; i < TOTAL_SPEAKERS; i++ )
  {
    currentPitch[i] = 0;
  }
  firstPitch = true;
}

void XibStave::loop ( bool activateLoop )
{
  inLoop = activateLoop;
}

void XibStave::addStave ( uint8_t *stave, uint16_t staveTotalPitches,
                          uint8_t pinSpeaker )
{
  staves[ indexTotalSpeakers ] = stave;

  totalPitches[ indexTotalSpeakers ] = staveTotalPitches;

  tones[ indexTotalSpeakers ].begin( pinSpeaker );

  pinMode( pinSpeaker, OUTPUT );

  indexTotalSpeakers++;
}

void XibStave::begin ()
{
  for ( uint8_t i = 0; i < 8; i++ )
  {
    durations[ i ] = durationsForCalc[ i ];
  }
}

void XibStave::run ()
{
  if ( playing )
  {
    for ( uint8_t i = 0; i < TOTAL_SPEAKERS; i++ )
    {
      if ( !staveFinished( i ) )
      {

        /**
         * When the first pitch is reproduced, prevtime[x] has a value 0, so the duration it's wrong
         */
        if ( firstPitch )
        {
          prevTime[ i ] = millis();
          firstPitch = false;
        }
        currentTime[ i ] = millis();



        /**
         * |============NoiseDuration========|==SilenceDuration==|
         * |====================PitchDuration====================|
         */
        if ( currentTime[ i ] - prevTime[ i ] >= getCurrentDurationFromStave( i ) - silenceDuration )
        {
          tones[ i ].stop();
        }
        else
        {
          /**
            * Play the note, unless its a SILENCE (END)
            */
          uint16_t pitchFrec = getCurrentPitchFromStave( i );
          if ( pitchFrec != pitchesFrec[ END ] )
          {
            tones[ i ].play( pitchFrec );
          }
          else
          {
            tones[ i ].stop();
          }
        }
        
        
        
        /**
         * Start new pitch when duration finish
         */
        
        if ( currentTime[ i ] - prevTime[ i ] >= getCurrentDurationFromStave( i ) )
        {
          prevTime[ i ] = currentTime[ i ];
          tones[ i ].stop();
          currentPitch[ i ]++;
        }
      }
    }
    repeatSong();
  }
}

void XibStave::setBPM ( uint8_t newBPM )
{
  musicBPM = newBPM;
}

void XibStave::setSilenceDuration ( uint16_t newSilenceDuration )
{
  silenceDuration = newSilenceDuration;
}

bool XibStave::staveFinished ( uint8_t indexStave )
{
  return currentPitch[ indexStave ] >= totalPitches[ indexStave ];
}

uint16_t XibStave::getCurrentPitchFromStave ( uint8_t stave )
{
  return pitchesFrec[ *( staves[ stave ] + ( currentPitch[ stave ] * 2 ) ) ];
}

uint16_t XibStave::getCurrentDurationFromStave ( uint8_t stave )
{
  return durations[ *( staves[ stave ] + ( currentPitch[ stave ] * 2 ) + 1 ) ];
}

void XibStave::repeatSong ()
{
  if ( inLoop )
  {
    for ( uint8_t i = 0; i < TOTAL_SPEAKERS; i++ )
    {
      if ( !staveFinished( i ) )
      {
        return;
      }
    }
    stop();
    play();
  }
}
