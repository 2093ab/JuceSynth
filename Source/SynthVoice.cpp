/*
  ==============================================================================

    SynthVoice.cpp
    Created: 7 Mar 2022 1:47:02pm
    Author:  길수민

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    currentAngle = 0.0f;
    level = velocity * 0.15;
    tailOff = 0.0;
    
    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();
    
    angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else{
        clearCurrentNote();
        angleDelta = 0.0;
    }
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchValue)
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannles)
{
    adsr.setSampleRate (sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannles;
    
    osc.prepare (spec);
    gain.prepare (spec);
    
    gain.setGainLinear (0.01f);
    
    adsrParams.attack = 0.8f;
    adsrParams.decay = 0.8f;
    adsrParams.sustain = 1.0f;
    adsrParams.release = 1.5f;

    adsr.setParameters (adsrParams);
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    //jassert(isPrepared);
    /*
    if (! isVoiceActive())
        return ;
    
    synthBuffer.setSize (outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    
    if (adsr.isActive())
        osc.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    else
        osc2.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    if (adsr.isActive())
        adsr.applyEnvelopeToBuffer (synthBuffer, 0, synthBuffer.getNumSamples());
    else
        adsr2.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    //if (startSample != 0)
        // jassertfalse;
    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom (channel, startSample, synthBuffer, channel, 0, numSamples);
        if (! adsr.isActive())
            clearCurrentNote();
    }*/
    if (angleDelta != 0.0)
    {
        if (tailOff > 0.0)
        {
            while (--numSamples >= 0)
            {
                auto currentSample = (float) (std::sin (currentAngle) * level * tailOff);
                
                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                
                currentSample += angleDelta;
                ++startSample;
                
                tailOff *= 0.99;
                
                if (tailOff <= 0.005)
                {
                    clearCurrentNote();
                    
                    angleDelta = 0.0;
                    break;
                }
            }
        }
        else
        {
            while (--numSamples >= 0)
            {
                auto currentSample = (float) (std::sin (currentAngle) * level);
                
                for (auto i = outputBuffer.getNumChannels();--i>=0;)
                    outputBuffer.addSample (i, startSample, currentSample);
                
                currentAngle += angleDelta;
                ++startSample;
            }
        }
    }
}
