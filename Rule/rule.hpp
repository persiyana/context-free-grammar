#pragma once

#include <iostream>
#include <vector>

class Rule
{
public:
    Rule() = default;
    Rule(char variable, std::vector<std::string> rules);
    
private:
    char variable = '\0';
    std::vector<std::string> rules;
    int ruleId = -1;
    static unsigned count;
};

unsigned Rule::count = 0;