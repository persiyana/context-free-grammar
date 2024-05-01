
#include "rule.hpp"

Rule::Rule(char variable, std::vector<std::string> rules)
:  variable(variable), rules(rules)
{}

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
}

void Rule::print(){
    std::cout <<  variable << std::endl;
    for (size_t i = 0; i < rules.size(); i++)
    {
        std::cout<< "   " <<rules[i];
    }
    std::cout << std::endl;
}