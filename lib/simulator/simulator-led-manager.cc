#include <chrono>

#include "audio-manager.h"
#include "simulator-led-manager.h"

extern void AudioCallback(void* userdata, uint8_t* stream, int len);

SimulatorLedManager::SimulatorLedManager() {
}

bool SimulatorLedManager::InitAudio(int device_id) {
  if (device_id < 0) {
    // Print audio devices
    int num_devices = SDL_GetNumAudioDevices(SDL_TRUE);
    if (num_devices < 1) {
      printf("No recording devices found.\n");
      return false;
    }

    printf("\nAudio capture devices:\n");
    for (int i = 0; i < num_devices; i++) {
      printf("%2d: %s\n", i, SDL_GetAudioDeviceName(i, SDL_TRUE));
    }

    SDL_AudioSpec requested_spec;
    SDL_zero(requested_spec);
    requested_spec.freq = 44100;
    // Use float, because kissfft only works with float or fixed point.
    requested_spec.format = AUDIO_F32;
    requested_spec.channels = 1;
    requested_spec.samples = AudioManager::kFftSize * 2;
    requested_spec.callback = AudioCallback;

    audio_device_id = SDL_OpenAudioDevice(NULL, /* iscapture */ SDL_TRUE, &requested_spec, nullptr, 0);
    if (audio_device_id == 0) {
      LogSDLError("SDL_OpenAudioDevice");
      return false;
    }
    device_id = audio_device_id;
    SDL_PauseAudioDevice(audio_device_id, 0);
    return true;
  }

  return false;
}

void SimulatorLedManager::CloseAudio() {
  if (audio_device_id >= 0) {
    SDL_CloseAudioDevice(audio_device_id);
  }
}

CRGB* SimulatorLedManager::GetLeds() {
  return leds;
}

void SimulatorLedManager::UpdateLeds() {
}

uint32_t SimulatorLedManager::GetMillis() {
  static const std::chrono::steady_clock::time_point start_time =
      std::chrono::steady_clock::now();

  const std::chrono::steady_clock::time_point end_time =
      std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end_time -
                                                               start_time)
      .count();
}

SDL_Point SimulatorLedManager::GetInitialSize() {
  SDL_DisplayMode display_mode;
  if (SDL_GetCurrentDisplayMode(0, &display_mode)) {
    this->LogSDLError("SDL_GetCurrentDisplayMode");
    return {1000, 600};
  } else {
    return {display_mode.w - 180, display_mode.h - 180};
  }
}

SDL_Point SimulatorLedManager::GetInitialPosition() {
  return {0, 0};
}

void SimulatorLedManager::GraphFft(const std::vector<uint16_t> fft) {
  int scale = 1;
  int height = 550;
  int width = 1000;
  if (SDL_GetRendererOutputSize(this->renderer_, &width, &height)) {
    this->LogSDLError("SDL_GetRendererOutputSize");
  }
  int line_size = width / fft.size();
  int max_height = height - (this->led_frame_pixels_ + kLedMarginPixels * 3 + line_size * 2);
  height -= line_size * 2;

  SDL_SetRenderDrawColor(renderer_, 0x40, 0x40, 0x40, 0xFF);
  SDL_Rect bottom = {0, height + line_size, line_size * fft.size(), line_size};
  SDL_RenderFillRect(renderer_, &bottom);

  for (int i = 0; i < fft.size(); i++) {
    int val = fft[i] / scale;
    if (val >= max_height) {
      val = max_height;
      SDL_SetRenderDrawColor(renderer_, 0xFF, 0x00, 0x00, 0xFF);
    } else {
      SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    SDL_Rect rect = {i * line_size, height - val, line_size, line_size};
    SDL_RenderFillRect(renderer_, &rect);
  }
}

bool SimulatorLedManager::EnableAudio() {
  return true;
}

void SimulatorLedManager::DrawExtras() {
  if (!fft_.empty()) {
    GraphFft(fft_);
  }
}

void SimulatorLedManager::set_fft(const std::vector<uint16_t> fft) {
  fft_ = fft;
}
