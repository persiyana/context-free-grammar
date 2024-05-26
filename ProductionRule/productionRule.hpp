#pragma once

#include <iostream>
#include <vector>
#include <fstream> 
#include <algorithm>

#include "../HelperFunctions/helperFunctions.hpp"

class ProductionRule
{
public:
    ProductionRule() = default;
    ProductionRule(char variable, const std::vector<std::string>& rules);
    ProductionRule(char variable, char rule);
    ProductionRule(char variable, const std::string& rule);

    void setVariable(char variable);
    char getVariable() const;
    void changeVariable(char oldVariable, char newVariable);
    void removeVariable(char variable);

    void addRule(const std::string& rule);
    void setRules(const std::vector<std::string>& rules);
    bool containsEpsilon() const;
    bool chomsky() const;
    std::vector<std::string> getRules() const;

    void display(std::ostream& out = std::cout) const;
    
    //checks if there is a product that contains only that letter
    bool hasLetterAsProduct(char letter) const;
    
    bool isTerminal(char letter) const;
    bool isVariable(char letter) const;

    bool isNullable(const std::vector<char>& nullableVariables) const;
    void replaceNullable(const std::vector<char>& nullableVariables);
    
private:
    char variable = '\0';
    std::vector<std::string> rules;
};
