/*
  ==============================================================================

    PluginParameters.h
    Created: 5 Jan 2024 12:49:32pm
    Author:  paulm

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include <string>

namespace Parameters {
    static const std::string apvtsIdentifier = "State";
    static const int apvtsVersion = 1;

    static const std::string sampleAttackTimeId = "sample_attack_time";
    static constexpr float sampleAttackTimeMinimumValue = 0.001f;
    static constexpr float sampleAttackTimeMaximumValue = 5.0f;
    static constexpr float sampleAttackTimeIntervalValue = 0.001f;
    static constexpr float sampleAttackTimeDefaultValue = 0.003f;
    static const juce::NormalisableRange<float> sampleAttackTimeNormalisableRange =
        juce::NormalisableRange<float>(
            sampleAttackTimeMinimumValue,
            sampleAttackTimeMaximumValue,
            sampleAttackTimeIntervalValue);

    static const std::string sampleDecayTimeId = "sample_decay_time";
    static constexpr float sampleDecayTimeMinimumValue = 0.001f;
    static constexpr float sampleDecayTimeMaximumValue = 3.0f;
    static constexpr float sampleDecayTimeIntervalValue = 0.001f;
    static constexpr float sampleDecayTimeDefaultValue = 0.5f;
    static const juce::NormalisableRange<float> sampleDecayTimeNormalisableRange =
        juce::NormalisableRange<float>(
            sampleDecayTimeMinimumValue,
            sampleDecayTimeMaximumValue,
            sampleDecayTimeIntervalValue);

    static const std::string sampleSustainLevelId = "sample_sustain_level";
    static constexpr float sampleSustainLevelMinimumValue = 0.0f;
    static constexpr float sampleSustainLevelMaximumValue = 1.0f;
    static constexpr float sampleSustainLevelIntervalValue = 0.001f;
    static constexpr float sampleSustainLevelDefaultValue = 1.0f;
    static const juce::NormalisableRange<float> sampleSustainLevelNormalisableRange =
        juce::NormalisableRange<float>(
            sampleSustainLevelMinimumValue,
            sampleSustainLevelMaximumValue,
            sampleSustainLevelIntervalValue);

    static const std::string sampleReleaseTimeId = "sample_release_time";
    static constexpr float sampleReleaseTimeMinimumValue = 0.001f;
    static constexpr float sampleReleaseTimeMaximumValue = 5.0f;
    static constexpr float sampleReleaseTimeIntervalValue = 0.001f;
    static constexpr float sampleReleaseTimeDefaultValue = 0.010f;
    static const juce::NormalisableRange<float> sampleReleaseTimeNormalisableRange =
        juce::NormalisableRange<float>(
            sampleReleaseTimeMinimumValue,
            sampleReleaseTimeMaximumValue,
            sampleReleaseTimeIntervalValue);

    static const std::vector<std::string> parameterIds = {
        sampleAttackTimeId,
        sampleDecayTimeId,
        sampleSustainLevelId,
        sampleReleaseTimeId
    };

    enum class ParameterEnum {
        SampleAttackTime,
        SampleDecayTime,
        SampleSustainLevel,
        SampleReleaseTime,
    };

    static const std::map<std::string, ParameterEnum> parameterIdToEnumMap{
    {sampleAttackTimeId, ParameterEnum::SampleAttackTime},
    {sampleDecayTimeId, ParameterEnum::SampleDecayTime},
    {sampleSustainLevelId, ParameterEnum::SampleSustainLevel},
    {sampleReleaseTimeId, ParameterEnum::SampleReleaseTime},
    };
}