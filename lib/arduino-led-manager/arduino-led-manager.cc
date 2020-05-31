#include "led-manager.h"
#include "arduino-led-manager.h"

CRGB* ArduinoLedManager::GetLeds() {
  return leds_;
}

void ArduinoLedManager::UpdateLeds() {
}

uint32_t ArduinoLedManager::GetMillis() {
  return millis();
}
