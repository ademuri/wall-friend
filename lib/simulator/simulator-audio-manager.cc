#include <cmath>
#include "simulator-audio-manager.h"

SimulatorAudioManager::SimulatorAudioManager() {
  kissfft_ = new kissfft<float>(kFftSize, /* inverse */ false);
  beat_kissfft_ = new kissfft<float>(beat_fft_size, /* inverse */ false);
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
    float scaled_magnitude = std::abs(result[i].real()) * 50;
    if (scaled_magnitude > 0xFFFF) {
      printf("Result out of bound: %.0f\n", scaled_magnitude);
    }
    fft_[i] = static_cast<uint16_t>(scaled_magnitude);
  }

  float low_freq_sum = 0;
  for (int i = 0; i < low_freq_bands; i++) {
    low_freq_sum += fft_[i];
  }
  low_freq_sum /= low_freq_bands;

  beat_accumulator += low_freq_sum;
  beat_accumulator_size++;
  if (beat_accumulator_size >= beat_accumulator_max_size) {
    beat_buffer.push_back(beat_accumulator);
    beat_accumulator = 0;
    beat_accumulator_size = 0;
  }

  if (beat_buffer.size() == beat_fft_size) {
    std::complex<float> complex_result[beat_fft_size];
    std::vector<uint16_t> result;
    beat_kissfft_->transform_real(beat_buffer.data(), complex_result);
    for (int i = 0; i < beat_fft_size; i++) {
      float raw_magnitude = std::abs(complex_result[i].real());
      float magnitude = raw_magnitude / (static_cast<float>(beat_accumulator_max_size));
      if (magnitude > 0xFFFF) {
        printf("2nd order FFT out of bounds: %.0f, %.0f\n", raw_magnitude, magnitude);
      }
      result.push_back(magnitude);
    }
    beat_fft_ = result;
    
    beat_buffer.clear();
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

std::vector<uint16_t> SimulatorAudioManager::GetFft() {
  return fft_;
}

std::vector<uint16_t> SimulatorAudioManager::GetBeatFft() {
  return beat_fft_;
}
