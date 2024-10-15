#pragma once

class Waveform {
public:
    virtual ~Waveform() = default;
    virtual float generate(float time) = 0;
    virtual void setFrequency(float frequency) = 0;
    virtual void setAmplitude(float amplitude) = 0;
    virtual void setPhase(float phase) = 0;
protected:
    float frequency = 1.0f;
    float amplitude = 1.0f;
    float phase = 0.0f;
};
