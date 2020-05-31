#include "arduino-led-manager.h"
#include "brain.h"

ArduinoLedManager* led_manager;
Brain* brain;

void setup() {
  led_manager = new ArduinoLedManager();
  brain = new Brain(led_manager);
}

void loop() {
  brain->Think();
  led_manager->UpdateLeds();
}
