#ifndef BRAIN_H_
#define BRAIN_H_

#include "led-manager.h"

// Does the thinking. Contains the application logic, and uses
// abstraction layers for the hardware so that it can run both on
// Arduino and desktop.
class Brain {
  public:
    Brain(LedManager* led_manager);

    // Runs an iteration of the logic. Reads from sensor(s) and
    // updates the LEDs.
    void Think();

  private:
    LedManager *const led_manager_;
};

#endif  // BRAIN_H_
