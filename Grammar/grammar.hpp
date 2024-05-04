#pragma once

#include <vector>
#include <iostream>
#include <fstream> 
#include "../Rule/rule.hpp"

class Grammar
{
public: 
    //Grammar();
    //~Grammar();
    void addRule(const Rule&);
    void addLetterToAlphabet(char);
    void addLetterToVariables(char);
    void addStartVariable(char);
    void print(std::ofstream&);
    void setId(unsigned);
    void clear();
    std::string getId() {return id;}
    //static unsigned grammarsCount;
private:
    std::string id = "";
    bool alphabet[36]{false};
    bool variables[26]{false};
    char start_variable = '\0';
    std::vector<Rule> rules;
};