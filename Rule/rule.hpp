#pragma once

#include <iostream>
#include <vector>
#include <fstream> 

class Rule
{
public:
    Rule() = default;
    Rule(char variable, std::vector<std::string> rules);
    void setVariable(char);
    char getVariable() const;
    void addRule(std::string);
    void display(std::ostream& s = std::cout) const;
    bool containsE() const;
    void changeVariable(char, char);
    bool otherRules() const;
    bool isSmallLetterOrNumber(char) const;
    bool isCapitalLetter(char) const;
    bool hasLetter(char) const;
private:
    char variable = '\0';
    std::vector<std::string> rules;
    bool hasEpsilon = false;
};
