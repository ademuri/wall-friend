A color organ that responds to sound.

# Building

Wall Friend uses PlatformIO for building for Arduino, and CMake for building the simulator.

## Arduino

`platformio run`

## Simulator

The simulator depends on SDL2. To install the deps on Ubuntu:

```
sudo apt install libsdl2-dev
```

Then, to build and run the simulator:

```
mkdir -p build && cd build
cmake ..
make && ./wall-friend-simulator
```
