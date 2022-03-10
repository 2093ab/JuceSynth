/*
  ==============================================================================

    SynthVoice.h
    Created: 7 Mar 2022 1:47:02pm
    Author:  길수민

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannles);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
private:
    juce::ADSR adsr;
    juce::ADSR adsr2;
    juce::ADSR::Parameters adsrParams;
    juce::AudioBuffer<float> synthBuffer;
    
    juce::dsp::Oscillator<float> osc { [](float x) {return std::sin(x); } };
    juce::dsp::Oscillator<float> osc2 { [](float x) {return std::sin(x); } };
    juce::dsp::Gain<float> gain;
    bool isPrepared { false };
};
