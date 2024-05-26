#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "../FileManager/fileManager.hpp"
#include "../GrammarListManager/grammarListManager.hpp"
#include "../HelperFunctions/helperFunctions.hpp"

class Engine {
public:
    static Engine& getInstance();
    void run();

private:
    Engine() {}
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    void help() const;
    FileManager fileManager;
    GrammarListManager grammarListManager;
    void readConsole(std::string& command, std::string& arguments);
};