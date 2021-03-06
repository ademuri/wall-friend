#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_

#include <cstdint>
#include <vector>

// Abstraction layer for reading audio data and performing FFTs on it.
class AudioManager {
  public:
    // Returns true if new data is available.
    virtual bool Available() = 0;

    // Returns the most recent FFT results
    virtual std::vector<uint16_t> GetFft() = 0;

    static const int kFftSize = 128;
};

#endif  // AUDIO_MANAGER_H_
