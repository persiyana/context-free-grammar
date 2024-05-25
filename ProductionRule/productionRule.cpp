#include "productionRule.hpp"

ProductionRule::ProductionRule(char variable, std::vector<std::string> rules)
:  variable(variable), rules(rules) //todo validation
{}
ProductionRule::ProductionRule(char var, char rule)
{
    std::vector<std::string> rules;
    rules.push_back("");
    rules[0].push_back(rule);
    variable = var;
    this->rules = rules;
}
ProductionRule::ProductionRule(char var, std::string rule)
{
    std::vector<std::string> rules;
    rules.push_back(rule);
    variable = var;
    this->rules = rules;
}

char ProductionRule::getVariable() const 
{ 
    return variable;
}

void ProductionRule::setVariable(char letter)
{
    if(letter >= 'A' && letter <= 'Z')
    {

        variable = letter;
    }
}

void ProductionRule::addRule(std::string rule) //todo validation
{
    rules.push_back(rule);
    if(rule=="epsilon")
    {
        hasEpsilon = true;
    }
}

void ProductionRule::display(std::ostream& file) const{

    for (size_t i = 0; i < rules.size(); i++)
    {
        file<< " " <<rules[i];
    }

}

bool ProductionRule::getHasEpsilon() const{
    return hasEpsilon;
}

void ProductionRule::changeVariable(char oldVar, char newVar)
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

bool ProductionRule::otherRules() const
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

bool ProductionRule::isSmallLetterOrNumber(char letter) const
{
    return ((letter >= '0' && letter <='9') || (letter >= 'a' && letter <='z'));
}

bool ProductionRule::isCapitalLetter(char letter) const
{
    return (letter >= 'A' && letter <='Z');
}

bool ProductionRule::hasLetter(char letter) const
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

std::vector<std::string> ProductionRule::getRules() const
{
    return rules;
}

void ProductionRule::setRules(std::vector<std::string> newProductionRules)
{   
    rules = newProductionRules;
}

bool ProductionRule::isNullable(std::vector<char>& nullableVariables) const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if (rules[i] == "epsilon")
        {
            return true;
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

void ProductionRule::replaceNullable(std::vector<char> &nullableVariables)
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
                    std::string newProductionRule = rules[i];
                    newProductionRule.erase(newProductionRule.begin()+j);
                    if (std::find(rules.begin(), rules.end(), newProductionRule) == rules.end())
                    {
                        rules.push_back(newProductionRule);
                    }
                    
                }
            }           
        }
    }
    
}

void ProductionRule::removeVariable(char variable)
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(std::find(rules[i].begin(), rules[i].end(), variable) != rules[i].end())
        {
            rules.erase(rules.begin() + i);
        }
    }
}
