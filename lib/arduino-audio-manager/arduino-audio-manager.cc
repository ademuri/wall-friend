#include "arduino-audio-manager.h"

ArduinoAudioManager::ArduinoAudioManager() {
  patch_cord = new AudioConnection(adc, fft);
}

bool ArduinoAudioManager::Available() {
  return fft.available();
}

uint16_t* ArduinoAudioManager::GetFft() {
  return fft.output;
}
