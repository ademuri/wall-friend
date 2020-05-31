#include <cmath>
#include "simulator-audio-manager.h"

SimulatorAudioManager::SimulatorAudioManager() {
  kissfft_ = new kissfft<float>(kFftSize, /* inverse */ false);
}

void SimulatorAudioManager::AudioCallback(void* userdata, uint8_t* stream, int len) {
  // The buffer will be of length 2 * kFftSize, and be a 32-bit float.
  if (len != kFftSize * 2 * 4) {
    printf("Expected size: %d, got: %d\n", kFftSize * 4, len);
    return;
  }

  float* native_stream = (float*) stream;

  // Apply Hann window
  for (int i = 0; i < kFftSize; i++) {
    native_stream[i] = native_stream[i] * std::pow(sin(M_PI * i / (kFftSize)), 2);
  }

  std::complex<float> result[kFftSize];
  kissfft_->transform_real(native_stream, result);

  double max_value = 0xF00000;
  double scale_factor = 0xFFFE / max_value;

  for (int i = 0; i < kFftSize; i++) {
    // TODO: is this the right way to scale this?
    float scaled_magnitude = std::abs(result[i].real()) * 10;
    if (scaled_magnitude > 0xFFFF) {
      printf("Result out of bound: %.0f\n", scaled_magnitude);
    }
    fft_[i] = static_cast<uint16_t>(scaled_magnitude);
  }

  available_ = true;
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
