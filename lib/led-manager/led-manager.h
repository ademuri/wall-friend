#ifndef LED_MANAGER_H_
#define LED_MANAGER_H_

#include <FastLED.h>

class LedManager {
  public:
    static const int kNumLeds = 32;

    // Gets the LEDs
    virtual CRGB* GetLeds() = 0;

    // Writes out the LED values.
    virtual void UpdateLeds() = 0;
};

#endif  // LED_MANAGER_H_ 
