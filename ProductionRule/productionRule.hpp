#pragma once

#include <iostream>
#include <vector>
#include <fstream> 
#include <algorithm>

class ProductionRule
{
public:
    ProductionRule() = default;
    ProductionRule(char variable, std::vector<std::string> rules);
    ProductionRule(char, char);
    ProductionRule(char, std::string);
    void setVariable(char);
    char getVariable() const;
    void addRule(std::string);
    void setRules(std::vector<std::string>);
    void display(std::ostream& s = std::cout) const;
    bool getHasEpsilon() const;
    void changeVariable(char, char);
    bool otherRules() const;
    bool isSmallLetterOrNumber(char) const;
    bool isCapitalLetter(char) const;
    bool hasLetter(char) const;
    std::vector<std::string> getRules() const;
    bool isNullable(std::vector<char>& nullableVariables) const;
    void replaceNullable(std::vector<char>& nullableVariables);
    void removeVariable(char variable);
private:
    char variable = '\0';
    std::vector<std::string> rules;
    bool hasEpsilon = false;
};
