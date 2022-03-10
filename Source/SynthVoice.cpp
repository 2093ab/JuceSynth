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
    osc.setFrequency (juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    osc2.setFrequency (juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    if (adsr.isActive())
        adsr.noteOn();
    else
        adsr2.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    if (!adsr2.isActive())
        adsr2.noteOff();
    else
        adsr.noteOff();
    
    if (! allowTailOff)
        clearCurrentNote();
    
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
    adsr2.setParameters (adsrParams);
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
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
    }
}
