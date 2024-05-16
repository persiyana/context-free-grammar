#pragma once

#include <vector>
#include <iostream>
#include <fstream> 
#include <string> 

#include "../Rule/rule.hpp"

constexpr size_t ALPHABET_SIZE = 36;
constexpr size_t VARIABLES_SIZE = 26;
constexpr size_t DIGITS_COUNT = 10;

class Grammar
{
public: 
    void addRule(const Rule&);
    void addLetterToAlphabet(char);
    void addLetterToAlphabet(size_t);
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
    bool getAlphabet(size_t i) const;
    std::vector<Rule> getRules() const;
    void changeVariable(size_t letter, size_t unusedLetter);
    bool chomsky() const;
private:
    std::string id = "";
    bool alphabet[ALPHABET_SIZE]{false};
    bool variables[VARIABLES_SIZE]{false};
    char start_variable = '\0';
    std::vector<Rule> rules;
    
    void setId();
};