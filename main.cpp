/*#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "SineWave.h"
#include "SquareWave.h"

int main() {
    std::string waveformType;
    float frequency, amplitude, phase = 0.0f;
    int samples;
    float duration = 1.0f; // duration of 1 second

    // User input for waveform parameters
    std::cout << "Enter waveform type (sine or square): ";
    std::cin >> waveformType;
    std::cout << "Enter frequency (Hz): ";
    std::cin >> frequency;
    std::cout << "Enter amplitude: ";
    std::cin >> amplitude;
    std::cout << "Enter phase shift (optional, default 0): ";
    std::cin >> phase;
    std::cout << "Enter the number of samples: ";
    std::cin >> samples;

    // Create appropriate waveform instance based on user input
    std::unique_ptr<Waveform> waveform;
    if (waveformType == "sine") {
        waveform = std::make_unique<SineWave>();
    } else if (waveformType == "square") {
        waveform = std::make_unique<SquareWave>();
    } else {
        std::cerr << "Invalid waveform type." << std::endl;
        return 1;
    }

    //
}
*/


#include <iostream>
#include <vector>
#include <fstream>
#include <cmath> // For sin() and M_PI
#include <string>

// Base class for waveform
class Waveform {
public:
    virtual ~Waveform() {}
    virtual float generate(float time) = 0; // Pure virtual function to generate waveform
    virtual void setFrequency(float frequency) = 0;
    virtual void setAmplitude(float amplitude) = 0;
    virtual void setPhase(float phase) = 0;
};

// Derived class for Sine Wave
class SineWave : public Waveform {
private:
    float frequency;
    float amplitude;
    float phase;

public:
    SineWave() : frequency(1.0), amplitude(1.0), phase(0.0) {}

    float generate(float time) override {
        return amplitude * sin(2 * M_PI * frequency * time + phase);
    }

    void setFrequency(float f) override { frequency = f; }
    void setAmplitude(float a) override { amplitude = a; }
    void setPhase(float p) override { phase = p; }
};

// Derived class for Square Wave
class SquareWave : public Waveform {
private:
    float frequency;
    float amplitude;
    float phase;

public:
    SquareWave() : frequency(1.0), amplitude(1.0), phase(0.0) {}

    float generate(float time) override {
        return amplitude * (sin(2 * M_PI * frequency * time + phase) >= 0 ? 1 : -1);
    }

    void setFrequency(float f) override { frequency = f; }
    void setAmplitude(float a) override { amplitude = a; }
    void setPhase(float p) override { phase = p; }
};

// Function to save waveform data to a CSV file
void saveToCSV(const std::vector<float>& time, const std::vector<float>& amplitude, const std::string& filename) {
    std::ofstream file(filename);
    
    // Check if file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    // Write header
    file << "Time,Amplitude\n";

    // Write data
    for (size_t i = 0; i < time.size(); ++i) {
        file << time[i] << "," << amplitude[i] << "\n";
    }

    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}

int main() {
    std::string waveformType;
    float frequency, amplitude, phase = 0.0;
    int numSamples;

    // User input
    std::cout << "Enter waveform type (sine or square): ";
    std::cin >> waveformType;
    std::cout << "Enter frequency (Hz): ";
    std::cin >> frequency;
    std::cout << "Enter amplitude: ";
    std::cin >> amplitude;
    std::cout << "Enter phase shift (optional, default 0): ";
    std::cin >> phase;
    std::cout << "Enter the number of samples: ";
    std::cin >> numSamples;

    // Create the appropriate waveform instance
    Waveform* waveform = nullptr;
    if (waveformType == "sine") {
        waveform = new SineWave();
    } else if (waveformType == "square") {
        waveform = new SquareWave();
    } else {
        std::cerr << "Unknown waveform type!" << std::endl;
        return 1;
    }

    // Set waveform parameters
    waveform->setFrequency(frequency);
    waveform->setAmplitude(amplitude);
    waveform->setPhase(phase);

    // Generate waveform data
    std::vector<float> time(numSamples);
    std::vector<float> amplitudeData(numSamples);
    float sampleInterval = 1.0 / numSamples; // Sampling rate

    for (int i = 0; i < numSamples; ++i) {
        time[i] = i * sampleInterval; // Time from 0 to 1 second
        amplitudeData[i] = waveform->generate(time[i]);
    }

    // Save the data to a CSV file
    saveToCSV(time, amplitudeData, "waveform.csv");

    // Clean up
    delete waveform;

    return 0;
}
