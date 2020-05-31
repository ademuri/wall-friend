#ifndef SIMULATOR_LED_MANAGER_H_
#define SIMULATOR_LED_MANAGER_H_

#include "led-manager.h"
#include "linear-simulator.h"

class SimulatorLedManager : public LedManager, public LinearSimulator<LedManager::kNumLeds> {
  public:
    SimulatorLedManager();

    CRGB* GetLeds() override;
    void UpdateLeds() override;
};

#endif  // SIMULATOR_LED_MANAGER_H_
