#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "../FileManager/fileManager.hpp"
#include "../GrammarListManager/grammarListManager.hpp"
#include "../HelperFunctions/helperFunctions.hpp"

class Engine
{
public:
    void run();

private:
    void help() const;
    FileManager fileManager;
    GrammarListManager grammarListManager;
};