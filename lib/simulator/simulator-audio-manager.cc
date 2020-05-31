#include "simulator-audio-manager.h"

SimulatorAudioManager::SimulatorAudioManager() {
}

bool SimulatorAudioManager::Available() {
  if (available_) {
    available_ = false;
    return true;
  }
  return false;
}

uint16_t* SimulatorAudioManager::GetFft() {
  return fft_;
}
