/*
  ==============================================================================

    AdsrGui.cpp
    Created: 26 May 2022 1:27:43pm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrGui.h"

//==============================================================================
AdsrGui::AdsrGui (juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    makeSlider (attackSlider, apvts, "ATTACK", attackAttachment);
    makeSlider (decaySlider, apvts, "DECAY", decayAttachment);
    makeSlider (sustainSlider, apvts, "SUSTAIN", sustainAttachment);
    makeSlider (releaseSlider, apvts, "RELEASE", releaseAttachment);
    /*release.setTextBoxStyle (juce::Slider::TextBoxAbove, true, 100, 30);
    release.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    release.setSkewFactor (0.1f);
    release.setColour (juce::Slider::textBoxTextColourId, juce::Colours::dimgrey);
    addAndMakeVisible (release);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "RELEASE", release);*/
}

AdsrGui::~AdsrGui()
{
}

void AdsrGui::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::wheat);
}

void AdsrGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    attackSlider.setBounds (20, 20, 100, 100);
    decaySlider.setBounds (120, 20, 100, 100);
    sustainSlider.setBounds (20, 120, 100, 100);
    releaseSlider.setBounds (120, 120, 100, 100);
    
}

void AdsrGui::makeSlider(juce::Slider &slider, juce::AudioProcessorValueTreeState &apvts, juce::String apvtsId, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> &attachment)
{
    slider.setTextBoxStyle (juce::Slider::TextBoxAbove, true, 80, 30);
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setColour (juce::Slider::textBoxTextColourId, juce::Colours::dimgrey);
    addAndMakeVisible (slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, apvtsId, slider);
}
