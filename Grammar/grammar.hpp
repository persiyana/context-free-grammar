#pragma once

#include <vector>
#include <iostream>
#include <fstream> 
#include <string> 
#include <algorithm>
#include <unordered_set>

#include "../ProductionRule/productionRule.hpp"
#include "../HelperFunctions/helperFunctions.hpp"

constexpr size_t TERMINALS_SIZE = 36;
constexpr size_t VARIABLES_SIZE = 26;
constexpr size_t DIGITS_COUNT = 10;

class Grammar
{
public: 
    static unsigned grammarsCount;
    std::string getId() const;

    void addLetterToTerminals(char letter);
    void addLetterToTerminals(size_t index);
    bool getTerminal(size_t index) const;


    void addLetterToVariables(char letter);
    void addLetterToVariables(size_t index);
    char getUnusedVariable() const;
    bool getVariable(size_t index) const;
    void changeVariable(size_t letter, size_t unusedLetter);
   
    void addStartVariable(char letter);
    char getStartVariable() const;

    void addRule(const ProductionRule& rule);
    void removeRule(size_t index);
    std::vector<ProductionRule> getRules() const;
    
    void display(std::ostream& s = std::cout) const;
    void clear();
    bool chomsky() const;
    bool cyk(const std::string& word) const;
    bool isEmpty() const;
    void chomskifyRules();
private:
    std::string id = "";
    bool terminals[TERMINALS_SIZE]{false};
    bool variables[VARIABLES_SIZE]{false};
    char start_variable = '\0';
    std::vector<ProductionRule> rules;
    
    void setId();

    void eliminateUselessProduction();
    void eliminateEpsilonProduction();
    void eliminateUnitProduction();
    void replaceTerminals();
    void convertToTwoVariabless();

    bool productContainsValidData(const std::string& product);

    void removeVariable(char variable);
    char getVariableForRule(const std::string& rule);
    void getNullableVariables(std::vector<char>& nullableVariables) const;
    bool hasRuleWith(char variable, char letter) const;
    bool containsEpsilon() const;
};