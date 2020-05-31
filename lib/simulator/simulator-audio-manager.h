#ifndef SIMULATOR_AUDIO_MANAGER_H_
#define SIMULATOR_AUDIO_MANAGER_H_

#include <cstdint>

#include "audio-manager.h"

class SimulatorAudioManager : public AudioManager {
  public:
    SimulatorAudioManager();

    bool Available() override;
    uint16_t* GetFft() override;
    
  private:
    uint16_t fft_[kFftSize] = {0};
    bool available_ = false;
};

#endif  // SIMULATOR_AUDIO_MANAGER_H_
