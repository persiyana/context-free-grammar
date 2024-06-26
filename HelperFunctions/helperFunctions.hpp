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

    template <typename T, typename P>
    bool contains(const T& arr, const P& element)
    {
        for (size_t i = 0; i < arr.size(); i++)
        {
            if (arr[i] == element)
            {
                return true;
            }           
        }
        return false;
    }

}