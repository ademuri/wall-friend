#ifndef ARDUINO_AUDIO_MANAGER_H_
#define ARDUINO_AUDIO_MANAGER_H_

#include <Audio.h>

#include "audio-manager.h"

class ArduinoAudioManager : public AudioManager {
  public:
    ArduinoAudioManager();

    bool Available() override;
    uint16_t* GetFft() override;

  private:
    AudioInputAnalog adc;
    AudioAnalyzeFFT256 fft;
    AudioConnection* patch_cord;
};

#endif  // ARDUINO_AUDIO_MANAGER_H_
