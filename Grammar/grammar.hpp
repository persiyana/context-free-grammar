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
    void addRule(const ProductionRule&);
    void addLetterToTerminals(char);
    void addLetterToTerminals(size_t);
    void addLetterToVariables(char letter);
    void addLetterToVariables(size_t index);
    void addStartVariable(char);
    
    void display(std::ostream& s = std::cout) const;
    void clear();
    std::string getId() const;
    void removeRule(size_t);
    bool containsE() const;
    static unsigned grammarsCount;
    char getUnusedVariable() const;
    char getStartVariable() const;
    bool getVariable(size_t i) const;
    bool getTerminals(size_t i) const;
    std::vector<ProductionRule> getRules() const;
    void changeVariable(size_t letter, size_t unusedLetter);
    bool chomsky() const;
    bool cyk(const std::string& word) const;
    bool hasRule(char variable, char letter) const;
    void fixRules();
    void getNullableVariables(std::vector<char>& nullableVariables) const;
    bool isEmpty() const;
    
private:
    std::string id = "";
    bool terminals[TERMINALS_SIZE]{false};
    bool variables[VARIABLES_SIZE]{false};
    char start_variable = '\0';
    std::vector<ProductionRule> rules;
    
    void setId();
    void eliminateUselessProd();
    void eliminateEpsilonProd();
    void eliminateUnitProd();
    void replaceTerminals();
    void convertToTwoVars();
    bool isOfTerminals(char);
    bool isOfVariables(char);
    char hasSingleRule(std::string );
    void removeVariable(char variable);
};