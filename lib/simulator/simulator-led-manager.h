#ifndef SIMULATOR_LED_MANAGER_H_
#define SIMULATOR_LED_MANAGER_H_

#include "led-manager.h"
#include "linear-simulator.h"

class SimulatorLedManager : public LedManager, public LinearSimulator<LedManager::kNumLeds> {
  public:
    SimulatorLedManager();

    // Initializes an audio input device. If device_id is <0, prints the
    // existing audio devices and uses the "default" one. Returns false on failure.
    bool InitAudio(int device_id);
    void CloseAudio();

    CRGB* GetLeds() override;
    void UpdateLeds() override;
    uint32_t GetMillis() override;

    SDL_Point GetInitialSize() override;
    SDL_Point GetInitialPosition() override;

    void GraphFft(const uint16_t* fft);

    bool EnableAudio() override;

    void DrawExtras() override;

    void set_fft(uint16_t* fft);

  private:
    SDL_AudioDeviceID audio_device_id = -1;
    const uint16_t* fft_ = nullptr;
};

#endif  // SIMULATOR_LED_MANAGER_H_
