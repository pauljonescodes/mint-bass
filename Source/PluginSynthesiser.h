/*
  ==============================================================================

	PluginSynthesiser.h
	Created: 4 Jan 2024 3:29:26pm
	Author:  paulm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <string>

class PluginSynthesiser : public juce::Synthesiser
{
public:
	PluginSynthesiser();
	~PluginSynthesiser();

	void addResource(
		const std::string name,
		const int bitRate,
		const int bitDepth,
		const int midiNote,
		juce::AudioFormatManager& audioFormatManager
	);
};