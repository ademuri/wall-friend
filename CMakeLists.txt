cmake_minimum_required(VERSION 3.11)
project(wall-friend CXX)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-fetch-content)

# Generate the file needed for YCM integration
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

include(FetchContent)
include(fetch-content-shim)
include(ExternalProject)

FetchContent_Declare(smart-input-filter
    GIT_REPOSITORY      https://github.com/ademuri/smart-input-filter.git
    GIT_TAG             master
)
FetchContent_MakeAvailable(smart-input-filter)

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

FetchContent_Declare(kissfft
    GIT_REPOSITORY      https://github.com/ademuri/kissfft.git
    GIT_TAG             master
)
FetchContent_MakeAvailable(kissfft)

add_executable(wall-friend-simulator
  lib/simulator/simulator.cc
  lib/simulator/simulator-audio-manager.cc
  lib/simulator/simulator-led-manager.cc
  lib/brain/brain.cc
  lib/debug/debug.cc)

target_include_directories(wall-friend-simulator PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/led-manager>
    $<INSTALL_INTERFACE:lib/led-manager>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/audio-manager>
    $<INSTALL_INTERFACE:lib/audio-manager>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/brain>
    $<INSTALL_INTERFACE:lib/brain>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/debug>
    $<INSTALL_INTERFACE:lib/debug>
    PRIVATE lib/simulator)

target_link_libraries(wall-friend-simulator
  smart-input-filter
  fake-fast-led
  fast-led-simulator
  kissfft)
