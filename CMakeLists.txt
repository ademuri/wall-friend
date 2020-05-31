cmake_minimum_required(VERSION 3.11)
project(wall-friend CXX)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Generate the file needed for YCM integration
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include(FetchContent)
include(fetch)

FetchContent_Declare(fast-led-simulator
    GIT_REPOSITORY      https://github.com/ademuri/fast-led-simulator.git
    GIT_TAG             master
)
FetchContent_MakeAvailable(fast-led-simulator)

FetchContent_Declare(fake-fast-led
    GIT_REPOSITORY      https://github.com/ademuri/FakeFastLED.git
    GIT_TAG             master
)
FetchContent_MakeAvailable(fake-fast-led)

add_executable(wall-friend-simulator
  lib/simulator/simulator.cc
  lib/simulator/simulator-led-manager.cc
  lib/brain/brain.cc)

target_include_directories(wall-friend-simulator PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/led-manager>
    $<INSTALL_INTERFACE:lib/led-manager>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/brain>
    $<INSTALL_INTERFACE:lib/brain>
    PRIVATE lib/simulator)

target_link_libraries(wall-friend-simulator
  fake-fast-led
  fast-led-simulator)

