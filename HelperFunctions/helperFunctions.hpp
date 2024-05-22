#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm> 

namespace HelperFunctions
{
    std::string getFileNameFromDir(const std::string& fileDirectory);
    std::vector<std::string> split(const std::string& str, char delim = ' ');
    std::string uniteVector(const std::vector<std::string>& vect, char delim = ' ');
}