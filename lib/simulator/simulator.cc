#include <kissfft.hh>

#include "brain.h"
#include "simulator-led-manager.h"

int main() {
  kissfft<double>* fft = new kissfft<double>(256, false);

  SimulatorLedManager led_manager;
  Brain* brain = new Brain(&led_manager);
  led_manager.Init();

  while (led_manager.Run()) {
    brain->Think();
  }

  led_manager.Close();
}
