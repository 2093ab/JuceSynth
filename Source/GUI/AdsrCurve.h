/*
  ==============================================================================

    AdsrCurve.h
    Created: 16 Jun 2022 8:38:34pm
    Author:  Soomin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrCurve  : public juce::Component,
juce::AudioProcessorValueTreeState::Listener
{
public:
    AdsrCurve(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrCurve() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void parameterChanged(const juce::String& parameterID, float newValue) override;

private:
    juce::AudioProcessorValueTreeState& apvts;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrCurve)
};
