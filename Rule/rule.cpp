
#include "rule.hpp"

Rule::Rule(char variable, std::vector<std::string> rules)
: ruleId(++count), variable(variable), rules(rules)
{}