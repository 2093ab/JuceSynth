/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth_testAudioProcessorEditor::Synth_testAudioProcessorEditor (Synth_testAudioProcessor& p)
    : AudioProcessorEditor (&p),
        audioProcessor (p),
        adsr (audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    addAndMakeVisible (adsr);
}

Synth_testAudioProcessorEditor::~Synth_testAudioProcessorEditor()
{
}

//==============================================================================
void Synth_testAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::whitesmoke);
    
}

void Synth_testAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    adsr.setBounds (10, 10, 250, 250);
}
