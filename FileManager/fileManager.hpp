#pragma once

#include <iostream>

#include "../Grammar/grammar.hpp"
#include "../HelperFunctions/helperFunctions.hpp"
#include "../SharedData/sharedData.hpp"

class FileManager
{
private:
    std::string fileDirectory = "";
    std::string fileName = "";
    void display(std::ostream&) const;
    std::string getFileNameFromDir(const std::string& fileDirectory) const;
public:
    std::string open(const std::string& fileDirectory);
    std::string close();
    std::string save() const;
    std::string saveAs(const std::string& fileDirectory) const;
    std::string printGrammar(const std::string& id) const;
    std::string saveGrammar(const std::string& id, const std::string& fileDirectory) const;
    
};