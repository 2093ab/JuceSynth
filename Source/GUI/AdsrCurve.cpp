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

    adsrCurve.startNewSubPath (responseArea.getX(), responseArea.getY() + h);
    adsrCurve.lineTo (responseArea.getX() + w * attackValue * 0.25,
                      responseArea.getY());
    adsrCurve.lineTo (adsrCurve.getCurrentPosition().getX() + w * 0.25 * decayValue,
                      responseArea.getY() - sustainValue * h + h);
    adsrCurve.lineTo (adsrCurve.getCurrentPosition().getX() + w * 0.25,
                      responseArea.getY() + h - sustainValue * h);
    adsrCurve.lineTo (adsrCurve.getCurrentPosition().getX() + w * (0.25 / 3) * releaseValue,
                      responseArea.getY() + h);
    
    g.setColour (juce::Colours::black);
    g.drawRoundedRectangle (responseArea.toFloat(), 4.1f, 1.f);
    
    g.setColour (juce::Colours::orange);
    g.strokePath (adsrCurve, juce::PathStrokeType(2.f));
}

void AdsrCurve::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
