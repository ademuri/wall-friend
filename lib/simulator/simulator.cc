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
  Brain* brain = new Brain(&led_manager);
  led_manager.Init();
  led_manager.InitAudio(-1);

  uint32_t short_fft[LedManager::kNumLeds] = {0};
  const int bin_size = AudioManager::kFftSize / LedManager::kNumLeds;
  const float alpha = 0.5;

  while (led_manager.Run()) {
    brain->Think();
    if (audio_manager.Available()) {
      uint16_t* fft = audio_manager.GetFft();
      led_manager.set_fft(fft);

      for (int i = 0; i < LedManager::kNumLeds; i++) {
        uint32_t sum = 0;
        for (int j = 0; j < bin_size; j++) {
          sum += fft[i * bin_size + j];
        }
        short_fft[i] = short_fft[i] * alpha + sum * (1 - alpha);
        uint16_t scaled_value = short_fft[i] / 4;
        led_manager.GetLeds()[i] = CHSV(0, scaled_value > 256 ? 255 : 0, scaled_value);
      }
    }
  }

  led_manager.CloseAudio();
  led_manager.Close();
}
