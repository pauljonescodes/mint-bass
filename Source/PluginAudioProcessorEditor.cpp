/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginAudioProcessor.h"
#include "PluginAudioProcessorEditor.h"

//==============================================================================
PluginAudioProcessorEditor::PluginAudioProcessorEditor (PluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    DBG(__func__);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

PluginAudioProcessorEditor::~PluginAudioProcessorEditor()
{
    DBG(__func__);
}

//==============================================================================
void PluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // DBG(__func__);
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Mint Bass", getLocalBounds(), juce::Justification::centred, 1);
}

void PluginAudioProcessorEditor::resized()
{
    DBG(__func__);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
