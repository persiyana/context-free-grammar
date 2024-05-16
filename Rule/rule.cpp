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

void Rule::changeVariable(char oldVar, char newVar)
{
    if(variable == oldVar) 
    {
        variable = newVar;
    }

    for (size_t i = 0; i < rules.size(); i++)
    {
        for (size_t j = 0; j < rules[i].size(); j++)
        {
            if(rules[i][j] == oldVar)
            {
                rules[i][j] = newVar;
            }
        }
        
    }
    
}

bool Rule::otherRules() const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules[i].size()>2)
        {
            if(rules[i] != "epsilon")
            {
                return false;
            }
            
        }
        else if(rules[i].size()==1 && isSmallLetterOrNumber(rules[i][0]))
        {
        }
        else if(rules[i].size()==2 && isCapitalLetter(rules[i][0]) && isCapitalLetter(rules[i][1]))
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Rule::isSmallLetterOrNumber(char letter) const
{
    return ((letter >= '0' && letter <='9') || (letter >= 'a' && letter <='z'));
}

bool Rule::isCapitalLetter(char letter) const
{
    return (letter >= 'A' && letter <='Z');
}