#ifndef SIMULATOR_AUDIO_MANAGER_H_
#define SIMULATOR_AUDIO_MANAGER_H_

#include <cstdint>
#include <kissfft.hh>
#include <vector>

#include "audio-manager.h"

class SimulatorAudioManager : public AudioManager {
  public:
    SimulatorAudioManager();

    void AudioCallback(void* userdata, uint8_t* stream, int len);

    bool Available() override;
    std::vector<uint16_t> GetFft() override;
    std::vector<uint16_t> GetBeatFft();
    
  private:
    static const int beat_fft_size = 32;
    static const int beat_accumulator_max_size = 4;
    static const int low_freq_bands = 20;

    float beat_accumulator = 0;
    int beat_accumulator_size = 0;
    std::vector<float> beat_buffer;

    std::vector<uint16_t> fft_ = std::vector<uint16_t>(AudioManager::kFftSize, 0);
    std::vector<uint16_t> beat_fft_;
    bool available_ = false;

    kissfft<float>* kissfft_;
    kissfft<float>* beat_kissfft_;
};

#endif  // SIMULATOR_AUDIO_MANAGER_H_
