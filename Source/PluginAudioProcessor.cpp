/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginAudioProcessor.h"
#include "PluginAudioProcessorEditor.h"
#include "PluginConstants.h"
#include "PluginUtils.h"
#include <cassert>

//==============================================================================
PluginAudioProcessor::PluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput(Constants::inputBusName, juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput(Constants::outputBusName, juce::AudioChannelSet::stereo(), true)
#endif
	),
	mAudioFormatManagerPtr(std::make_unique<juce::AudioFormatManager>()),
	mSynthesiserPtr(std::make_unique<PluginSynthesiser>())
#endif
{
	DBG(__func__);

	mAudioFormatManagerPtr->registerBasicFormats();

	for (int resourceIndex = 0; resourceIndex < BinaryData::namedResourceListSize; resourceIndex++)
	{
		std::string resourceName = BinaryData::namedResourceList[resourceIndex];
		std::vector<std::string> parts = PluginUtils::split(resourceName, "_");

		switch (parts.size())
		{
		case 3:
			if (parts[0] == Constants::samplePrefix && PluginUtils::isDigit(parts[1]))
			{
				int midiNote = std::stoi(parts[1]);
				mSynthesiserPtr->addResource(
					resourceName,
					Constants::sampleBitRate,
					Constants::sampleBitDepth,
					midiNote,
					*mAudioFormatManagerPtr.get());
			}
			else
			{
				assert(false);
			}
			break;
		default:
			assert(false);
			break;
		}
	}
}

PluginAudioProcessor::~PluginAudioProcessor()
{
	DBG(__func__);
}

//==============================================================================
const juce::String PluginAudioProcessor::getName() const
{
	DBG(__func__);
	return JucePlugin_Name;
}

bool PluginAudioProcessor::acceptsMidi() const
{
	DBG(__func__);
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool PluginAudioProcessor::producesMidi() const
{
	DBG(__func__);
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool PluginAudioProcessor::isMidiEffect() const
{
	//DBG(__func__);
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double PluginAudioProcessor::getTailLengthSeconds() const
{
	DBG(__func__);
	return 0.0;
}

int PluginAudioProcessor::getNumPrograms()
{
	DBG(__func__);
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int PluginAudioProcessor::getCurrentProgram()
{
	DBG(__func__);
	return 0;
}

void PluginAudioProcessor::setCurrentProgram(int index)
{
	DBG(__func__);
}

const juce::String PluginAudioProcessor::getProgramName(int index)
{
	DBG(__func__);
	return {};
}

void PluginAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
	DBG(__func__);
}

//==============================================================================
void PluginAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	DBG(__func__);
	
	mSynthesiserPtr->setCurrentPlaybackSampleRate(sampleRate);
}

void PluginAudioProcessor::releaseResources()
{
	DBG(__func__);
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
	DBG(__func__);
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
	// Some plugin hosts, such as certain GarageBand versions, will only
	// load plugins that support stereo bus layouts.
	if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
		&& layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
		return false;

	// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
	if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
		return false;
#endif

	return true;
#endif
}
#endif

void PluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	{
		buffer.clear(i, 0, buffer.getNumSamples());
	}
		
	mSynthesiserPtr->renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool PluginAudioProcessor::hasEditor() const
{
	DBG(__func__);
	return false; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PluginAudioProcessor::createEditor()
{
	DBG(__func__);
	return new PluginAudioProcessorEditor(*this);
}

//==============================================================================
void PluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	DBG(__func__);
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void PluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	DBG(__func__);
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	DBG(__func__);
	return new PluginAudioProcessor();
}
