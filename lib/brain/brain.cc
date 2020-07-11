#include "brain.h"
#include "debug.h"

#include <cstdio>
#include <vector>

Brain::Brain(LedManager* led_manager, AudioManager* audio_manager) : led_manager_(led_manager), audio_manager_(audio_manager) {
}

void Brain::Think() {
  std::vector<uint16_t> fft = audio_manager_->GetFft();
  uint32_t volume = 0;
  for (int i = 0; i < AudioManager::kFftSize; i++) {
    volume += fft[i];
  }
  recent_volume = volume / 4 + (recent_volume * 3) / 4;
  recent_average = recent_volume / 4 + (recent_average * 3) / 4;
  float ratio = ((float) recent_volume) / recent_average;
  debug_printf("volume: %5d, %5d, %5d, %3.1f\n", volume, recent_volume, recent_average, ratio);

  for (int i = 0; i < LedManager::kNumLeds; i++) {
    //led_manager_->GetLeds()[i] = CHSV(led_manager_->GetMillis() / 10, 255, 255);
  }
}
