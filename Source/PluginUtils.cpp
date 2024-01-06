/*
  ==============================================================================

    PluginUtils.cpp
    Created: 4 Jan 2024 3:24:41pm
    Author:  paulm

  ==============================================================================
*/

#include "PluginUtils.h"

bool PluginUtils::isDigit(const std::string& str) 
{
    //DBG(__func__);

    return !str.empty() && std::find_if(str.begin(),
        str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end();
}

std::vector<std::string> PluginUtils::split(const std::string& string, const std::string& by) 
{
    //DBG(__func__);

    std::vector<std::string> result;
    size_t current, previous = 0;
    current = string.find(by);
    while (current != std::string::npos) {
        std::string token = string.substr(previous, current - previous);
        if (!token.empty()) {
            result.push_back(token);
        }
        previous = current + by.length();
        current = string.find(by, previous);
    }
    std::string token = string.substr(previous, current - previous);
    if (!token.empty()) {
        result.push_back(token);
    }
    return result;
}

std::string PluginUtils::toTitleCase(const std::string& str) {
    std::string result;
    bool nextUpper = true;

    for (char ch : str) {
        if (ch == '_') {
            nextUpper = true;
            result += " ";
        }
        else if (nextUpper) {
            result += std::toupper(ch);
            nextUpper = false; // Reset the flag
        }
        else {
            if (result.empty()) { // first letter in lowercase for camelCase
                result += std::tolower(ch);
            }
            else {
                result += ch; // preserve the original case for the rest
            }
        }
    }

    return result;
}