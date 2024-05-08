#include "rule.hpp"

Rule::Rule(char variable, std::vector<std::string> rules)
:  variable(variable), rules(rules) //todo validation
{}

char Rule::getVariable() const 
{ 
    return variable;
}

void Rule::setVariable(char letter)
{
    if(letter >= 'A' && letter <= 'Z')
    {

        variable = letter;
    }
}

void Rule::addRule(std::string rule) //todo validation
{
    rules.push_back(rule);
    if(rule=="epsilon")
    {
        hasEpsilon = true;
    }
}

void Rule::display(std::ostream& file) const{

    for (size_t i = 0; i < rules.size(); i++)
    {
        file<< " " <<rules[i];
    }

}

bool Rule::containsE() const{
    return hasEpsilon;
}