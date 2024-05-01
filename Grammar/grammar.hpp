#pragma once

#include <vector>

#include "../Rule/rule.hpp"

class Grammar
{
public: 
    void addRule(const Rule&);

private:
    bool alphabet[36]{false};
    bool variables[26]{false};
    char start_variable = '\0';
    std::vector<Rule> rules;
};