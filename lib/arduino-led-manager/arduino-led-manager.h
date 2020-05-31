#ifndef ARDUINO_LED_MANAGER_H_
#define ARDUINO_LED_MANAGER_H_

#include "led-manager.h"

class ArduinoLedManager : public LedManager {
  public:
    CRGB* GetLeds() override;
    void UpdateLeds() override;

  private:
    CRGB leds_[kNumLeds];
};

#endif  // ARDUINO_LED_MANAGER_H_
