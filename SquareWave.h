#pragma once
#include "Waveform.h"
#include <cmath>

class SquareWave : public Waveform {
public:
    float generate(float time) override {
        return (std::sin(2 * M_PI * frequency * time + phase) >= 0) ? amplitude : -amplitude;
    }

    void setFrequency(float freq) override { frequency = freq; }
    void setAmplitude(float amp) override { amplitude = amp; }
    void setPhase(float ph) override { phase = ph; }
};
