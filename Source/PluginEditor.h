/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/AdsrGui.h"
#include "GUI/AdsrCurve.h"

//==============================================================================
/**
*/
class Synth_testAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Synth_testAudioProcessorEditor (Synth_testAudioProcessor&);
    ~Synth_testAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Synth_testAudioProcessor& audioProcessor;
    AdsrGui adsr;
    AdsrCurve adsrCurve;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth_testAudioProcessorEditor)
};
