#pragma once

#include <vector>
#include <iostream>
#include <fstream> 
#include <string> 

#include "../Rule/rule.hpp"

class Grammar
{
public: 
    void addRule(const Rule&);
    void addLetterToAlphabet(char);
    void addLetterToVariables(char);
    void addStartVariable(char);
    void display(std::ostream& s = std::cout) const;
    void clear();
    std::string getId() const;
    void removeRule(size_t);
    bool containsE() const;
    static unsigned grammarsCount;
    char getUnusedVariable() const;
    char getStartVariable() const;
private:
    std::string id = "";
    bool alphabet[36]{false};
    bool variables[26]{false};
    char start_variable = '\0';
    std::vector<Rule> rules;
    
    void setId();
};