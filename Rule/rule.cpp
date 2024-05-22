#include "rule.hpp"

Rule::Rule(char variable, std::vector<std::string> rules)
:  variable(variable), rules(rules) //todo validation
{}
Rule::Rule(char var, char rule)
{
    std::vector<std::string> rules;
    rules.push_back("");
    rules[0].push_back(rule);
    variable = var;
    this->rules = rules;
}
Rule::Rule(char var, std::string rule)
{
    std::vector<std::string> rules;
    rules.push_back(rule);
    variable = var;
    this->rules = rules;
}

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

bool Rule::getHasEpsilon() const{
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

bool Rule::hasLetter(char letter) const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules[i].size() == 1 && rules[i][0]==letter)
        {
            return true;
        }
    }
    return false;
}

std::vector<std::string> Rule::getRules() const
{
    return rules;
}

void Rule::setRules(std::vector<std::string> newRules)
{   
    rules = newRules;
}

bool Rule::isNullable(std::vector<char>& nullableVariables) const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if (rules[i] == "epsilon")
        {
            return true;
            break;
        }

        bool allNullable = true;
        for (size_t j = 0; j < rules[i].size(); j++)
        {
            bool isFound = false;   
            for (size_t n = 0; n < nullableVariables.size(); n++)
            {
                if(rules[i][j] == nullableVariables[n])
                {
                    isFound = true;
                    break;
                }
            }
            if(!isFound)
            {
                allNullable = false;
            }
        }
        if(allNullable)
        {
            return true;
        }
    }
    return false;
}

void Rule::replaceNullable(std::vector<char> &nullableVariables)
{

    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules[i] == "epsilon")
        {
            rules.erase(rules.begin()+i);
        }
        else
        {
            for (size_t j = 0; j < rules[i].size(); j++)
            {
                if (std::find(nullableVariables.begin(), nullableVariables.end(), rules[i][j]) != nullableVariables.end())
                {
                    std::string newRule = rules[i];
                    newRule.erase(newRule.begin()+j);
                    if (std::find(rules.begin(), rules.end(), newRule) == rules.end())
                    {
                        rules.push_back(newRule);
                    }
                    
                }
            }
            
            
        }
    }
    
}

void Rule::removeVariable(char variable)
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(std::find(rules[i].begin(), rules[i].end(), variable) != rules[i].end())
        {
            rules.erase(rules.begin() + i);
        }
    }
    
}
