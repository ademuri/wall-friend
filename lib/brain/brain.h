#ifndef BRAIN_H_
#define BRAIN_H_

#include "audio-manager.h"
#include "led-manager.h"

#include "median-filter.h"

// Does the thinking. Contains the application logic, and uses
// abstraction layers for the hardware so that it can run both on
// Arduino and desktop.
class Brain {
  public:
    Brain(LedManager* led_manager, AudioManager* audio_manager);

    // Runs an iteration of the logic. Reads from sensor(s) and
    // updates the LEDs.
    void Think();

  private:
    static const uint32_t kMedianSize = 11;

    LedManager *const led_manager_;
    AudioManager *const audio_manager_;
    MedianFilter<uint32_t, uint32_t, kMedianSize> *volume_filter_;

    uint32_t recent_volume = 0;
    uint32_t recent_average = 0;
};

#endif  // BRAIN_H_
