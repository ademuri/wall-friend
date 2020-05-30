#ifndef LED_MANAGER_H_
#define LED_MANAGER_H_

#include <FastLED.h>

class LedManager {
  public:
    static const int kNumLeds = 32;

    CRGB leds[kNumLeds];

    // Writes out the LED values.
    virtual void UpdateLeds() = 0;
};

#endif  // LED_MANAGER_H_ 
