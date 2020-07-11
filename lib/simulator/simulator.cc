#include <vector>
#include <kissfft.hh>

#include "brain.h"
#include "simulator-audio-manager.h"
#include "simulator-led-manager.h"

SimulatorAudioManager audio_manager;

void AudioCallback(void* userdata, uint8_t* stream, int len) {
  audio_manager.AudioCallback(userdata, stream, len);
}

int main() {
  SimulatorLedManager led_manager;
  Brain* brain = new Brain(&led_manager, &audio_manager);
  led_manager.Init();
  led_manager.InitAudio(-1);

  uint32_t short_fft[LedManager::kNumLeds] = {0};
  const int bin_size = AudioManager::kFftSize / LedManager::kNumLeds;
  const float alpha = 0.5;

  const int beat_fft_size = 16;
  const int beat_accumulator_max_size = 24;
  const int low_freq_bands = 2;
  kissfft<float>* beat_fft = new kissfft<float>(beat_fft_size, /* inverse */ false);
  float beat_accumulator = 0;
  int beat_accumulator_size = 0;
  std::vector<float> beat_buffer;

  while (led_manager.Run()) {
    if (audio_manager.Available()) {
      brain->Think();
      //led_manager.set_fft(audio_manager.GetBeatFft());

      uint16_t* fft = audio_manager.GetFft();
      std::vector<uint16_t> fft_vector(fft, fft + AudioManager::kFftSize);
      led_manager.set_fft(fft_vector);

      /*for (int i = 0; i < LedManager::kNumLeds; i++) {
        uint32_t sum = 0;
        for (int j = 0; j < bin_size; j++) {
          sum += fft[i * bin_size + j];
        }
        short_fft[i] = short_fft[i] * alpha + sum * (1 - alpha);
        uint16_t scaled_value = short_fft[i] / 4;
        led_manager.GetLeds()[i] = CHSV(0, scaled_value > 256 ? 255 : 0, scaled_value);
      }*/
    }
  }

  led_manager.CloseAudio();
  led_manager.Close();
}
