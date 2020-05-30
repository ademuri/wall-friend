#ifndef ARDUINO_LED_MANAGER_H_
#define ARDUINO_LED_MANAGER_H_

#include "led-manager.h"

class ArduinoLedManager : public LedManager {
  public:
    void UpdateLeds() override;
};

#endif  // ARDUINO_LED_MANAGER_H_
