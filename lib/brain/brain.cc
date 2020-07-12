#include "brain.h"
#include "debug.h"

#include <cstdint>
#include <cstdio>
#include <vector>

Brain::Brain(LedManager* led_manager, AudioManager* audio_manager) : led_manager_(led_manager), audio_manager_(audio_manager) {
  volume_filter_ = new MedianFilter<uint32_t, uint32_t, kMedianSize>([this](){
    std::vector<uint16_t> fft = audio_manager_->GetFft();
    uint32_t volume = 0;
    for (int i = 0; i < AudioManager::kFftSize; i++) {
      volume += fft[i];
    }
    return volume;
  });
}

void Brain::Think() {
  volume_filter_->Run();
  uint32_t volume = volume_filter_->GetFilteredValue();
  recent_volume = volume / 4 + (recent_volume * 3) / 4;
  recent_average = recent_volume / 4 + (recent_average * 3) / 4;
  float ratio = ((float) volume) / recent_average;
  debug_printf("volume: %5d, %5d, %5d, %3.1f\n", volume, recent_volume, recent_average, ratio);

  if (ratio < 1) {
    float inverse = 1.0 / ratio;
    uint16_t brightness = inverse / 3.0 * 255;
    if (brightness > 255) {
      brightness = 255;
    }

    led_manager_->GetLeds()[0] = CHSV(100, 255, brightness);
  } else {
    uint16_t brightness = ratio / 3.0 * 255;
    if (brightness > 255) {
      brightness = 255;
    }

    led_manager_->GetLeds()[0] = CHSV(0, 255, brightness);
  }

  for (int i = 0; i < LedManager::kNumLeds; i++) {
    //led_manager_->GetLeds()[i] = CHSV(led_manager_->GetMillis() / 10, 255, 255);
  }
}
