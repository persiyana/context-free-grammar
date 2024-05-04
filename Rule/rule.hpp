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
    char getVariable() { return variable;}
    void addRule(std::string);
    void print(std::ofstream&);
    void print();
private:
    char variable = '\0';
    std::vector<std::string> rules;
    //int ruleId = -1;
    //static unsigned count;
};

//unsigned Rule::count = 0;