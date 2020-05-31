#include "arduino-audio-manager.h"
#include "arduino-led-manager.h"
#include "brain.h"

ArduinoAudioManager* audio_manager;
ArduinoLedManager* led_manager;
Brain* brain;

void setup() {
  audio_manager = new ArduinoAudioManager();
  led_manager = new ArduinoLedManager();
  brain = new Brain(led_manager);
}

void loop() {
  brain->Think();
  led_manager->UpdateLeds();
}
