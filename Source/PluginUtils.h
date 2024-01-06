/*
  ==============================================================================

    PluginUtils.h
    Created: 4 Jan 2024 3:24:41pm
    Author:  paulm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <string>
#include <vector>

class PluginUtils {
public:
	static bool isDigit(const std::string& str);
    
    static std::vector<std::string> split(
        const std::string& s, 
        const std::string& delim);

    static std::string toTitleCase(const std::string& str);
};