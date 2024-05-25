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
    ProductionRule(char variable, char rule);
    ProductionRule(char variable, std::string rule);

    void setVariable(char variable);
    char getVariable() const;
    void changeVariable(char oldVariable, char newVariable);
    void removeVariable(char variable);

    void addRule(std::string rule);
    void setRules(std::vector<std::string> rules);
    bool containsEpsilon() const;
    bool chomsky() const;
    std::vector<std::string> getRules() const;

    void display(std::ostream& out = std::cout) const;
    
    bool hasLetter(char letter) const;
    
    bool isTerminal(char letter) const;
    bool isVariable(char letter) const;

    bool isNullable(std::vector<char>& nullableVariables) const;
    void replaceNullable(std::vector<char>& nullableVariables);
    
private:
    char variable = '\0';
    std::vector<std::string> rules;
};
