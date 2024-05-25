#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm> 

namespace HelperFunctions
{
    std::vector<std::string> split(const std::string& str, char delim = ' ');
    std::string uniteVector(const std::vector<std::string>& vect, char delim = ' ');
    bool contains(const std::string& str, char ch);
}