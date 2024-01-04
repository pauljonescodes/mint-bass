/*
  ==============================================================================

    PluginSynthesiser.cpp
    Created: 4 Jan 2024 3:29:26pm
    Author:  paulm

  ==============================================================================
*/

#include "PluginSynthesiser.h"
#include "PluginConstants.h"

PluginSynthesiser::PluginSynthesiser()
{
    DBG(__func__);
}

PluginSynthesiser::~PluginSynthesiser()
{
    DBG(__func__);
}

void PluginSynthesiser::addResource(
    const std::string resourceName,
    const int bitRate,
    const int bitDepth,
    const int midiNote,
    juce::AudioFormatManager& audioFormatManager
) {
    DBG(__func__ + resourceName + " " + std::to_string(bitRate) + " " + std::to_string(bitDepth) + " " + std::to_string(midiNote));
    
    juce::BigInteger range;
    range.setRange(midiNote, 1, true);
    int dataSizeInBytes;

    const char* sourceData = BinaryData::getNamedResource(resourceName.c_str(), dataSizeInBytes);
    auto memoryInputStream = std::make_unique<juce::MemoryInputStream>(sourceData, dataSizeInBytes, false);
    juce::AudioFormatReader* reader = audioFormatManager.createReaderFor(std::move(memoryInputStream));

    double maxSampleLengthSeconds = dataSizeInBytes / (bitRate * (bitDepth / 8.0));
    juce::SamplerSound* sound = new juce::SamplerSound(
        juce::String(resourceName), 
        *reader, 
        range, 
        midiNote, 
        Constants::sampleAttackTimeSeconds, 
        Constants::sampleReleaseTimeSeconds,
        maxSampleLengthSeconds);

    addSound(sound);
    addVoice(new juce::SamplerVoice());
}
