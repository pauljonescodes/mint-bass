/*
  ==============================================================================

    PluginConstants.h
    Created: 4 Jan 2024 3:23:07pm
    Author:  paulm

  ==============================================================================
*/

#pragma once
#include <string>

namespace Constants {
    static const std::string inputBusName = "Input";
    static const std::string outputBusName = "Output";

    static const std::string samplePrefix = "Sample";
    
    static constexpr int sampleBitRate = 192000;
    static constexpr int sampleBitDepth = 24;
}