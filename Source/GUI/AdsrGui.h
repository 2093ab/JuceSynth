/*
  ==============================================================================

    AdsrGui.h
    Created: 26 May 2022 1:27:43pm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrGui  : public juce::Component
{
public:
    AdsrGui(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void makeSlider (
                     juce::Slider &slider,
                     juce::AudioProcessorValueTreeState &apvts,
                     juce::String apvtsId,
                     std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment);
private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrGui)
};
