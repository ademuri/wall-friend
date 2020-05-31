#include "brain.h"

Brain::Brain(LedManager* led_manager) : led_manager_(led_manager) {
}

void Brain::Think() {
  for (int i = 0; i < LedManager::kNumLeds; i++) {
    led_manager_->GetLeds()[i] = CHSV(led_manager_->GetMillis() / 10, 255, 255);
  }
}
