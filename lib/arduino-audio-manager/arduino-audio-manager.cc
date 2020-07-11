#include "arduino-audio-manager.h"

ArduinoAudioManager::ArduinoAudioManager() {
  patch_cord = new AudioConnection(adc, fft);
}

bool ArduinoAudioManager::Available() {
  return fft.available();
}

std::vector<uint16_t> ArduinoAudioManager::GetFft() {
  return std::vector<uint16_t>(fft.output, fft.output + AudioManager::kFftSize);
}
