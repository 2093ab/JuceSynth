/*
  ==============================================================================

    AdsrCurve.cpp
    Created: 16 Jun 2022 8:38:34pm
    Author:  Soomin

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrCurve.h"

//==============================================================================
void AdsrCurve::parameterChanged(const juce::String &parameterID, float newValue)
{
    repaint();
}

AdsrCurve::AdsrCurve(juce::AudioProcessorValueTreeState& apvts)
    :apvts (apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    apvts.addParameterListener ("ATTACK", this);
    apvts.addParameterListener ("DECAY", this);
    apvts.addParameterListener ("SUSTAIN", this);
    apvts.addParameterListener ("RELEASE", this);
}

AdsrCurve::~AdsrCurve()
{
    apvts.removeParameterListener ("ATTACK", this);
    apvts.removeParameterListener ("DECAY", this);
    apvts.removeParameterListener ("SUSTAIN", this);
    apvts.removeParameterListener ("RELEASE", this);
}

void AdsrCurve::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::wheat);   // clear the background
    
    auto responseArea = getLocalBounds().reduced (0, 50);
    auto w = responseArea.getWidth();
    auto h = responseArea.getHeight();
    juce::Path adsrCurve;

    auto attackValue = apvts.getRawParameterValue ("ATTACK")->load();
    auto decayValue = apvts.getRawParameterValue ("DECAY")->load();
    auto sustainValue = apvts.getRawParameterValue ("SUSTAIN")->load();
    auto releaseValue = apvts.getRawParameterValue ("RELEASE")->load();

    adsrCurve.startNewSubPath (responseArea.getX(), responseArea.getBottom());
    adsrCurve.quadraticTo (responseArea.getX(), responseArea.getY(),
                           responseArea.getX() + w * 0.125 * (attackValue + 1),
                           responseArea.getY());
    adsrCurve.quadraticTo (adsrCurve.getCurrentPosition().getX(),
                           responseArea.getBottom() - sustainValue * h,
                           adsrCurve.getCurrentPosition().getX() + w * 0.125 *(decayValue + 1),
                           responseArea.getBottom() - sustainValue * h);
    adsrCurve.lineTo (adsrCurve.getCurrentPosition().getX() + w * 0.25,
                      adsrCurve.getCurrentPosition().getY());
    adsrCurve.quadraticTo (adsrCurve.getCurrentPosition().getX(),
                           responseArea.getBottom(),
                           adsrCurve.getCurrentPosition().getX() + w * ((0.25 / 2) +
                           (0.25 / 6) * releaseValue), responseArea.getBottom());
    adsrCurve.closeSubPath();
    
    g.setColour (juce::Colours::black);
    g.drawRoundedRectangle (getLocalBounds().reduced(0, 49).toFloat(), 1.1f, 1.f);
    
    g.setColour (juce::Colours::orange);
    g.fillPath (adsrCurve);
}

void AdsrCurve::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
