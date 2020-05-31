#ifndef SIMULATOR_AUDIO_MANAGER_H_
#define SIMULATOR_AUDIO_MANAGER_H_

#include <cstdint>
#include <kissfft.hh>

#include "audio-manager.h"

class SimulatorAudioManager : public AudioManager {
  public:
    SimulatorAudioManager();

    void AudioCallback(void* userdata, uint8_t* stream, int len);

    bool Available() override;
    uint16_t* GetFft() override;
    
  private:
    uint16_t fft_[kFftSize] = {0};
    bool available_ = false;

    kissfft<float>* kissfft_;
};

#endif  // SIMULATOR_AUDIO_MANAGER_H_
