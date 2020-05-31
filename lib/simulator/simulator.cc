#include "simulator-led-manager.h"

int main() {

  SimulatorLedManager led_manager;
  led_manager.Init();

  while (led_manager.Run()) {
  }

  led_manager.Close();
}
