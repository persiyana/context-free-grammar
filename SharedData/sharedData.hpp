#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../Grammar/grammar.hpp"

class SharedData
{
public:
    static std::vector<Grammar> grammarList;
    static int indexOfId(const std::string& id);
};