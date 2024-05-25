#include "productionRule.hpp"

//constructors
ProductionRule::ProductionRule(char letter, std::vector<std::string> initialRules)
{
    setVariable(letter);
    setRules(initialRules);
}

ProductionRule::ProductionRule(char letter, char rule)
{
    setVariable(letter);
    addRule(std::string(1, rule));
}

ProductionRule::ProductionRule(char letter, std::string rule)
{
    setVariable(letter);
    addRule(rule);
}

//variable
void ProductionRule::setVariable(char letter)
{
    if(letter >= 'A' && letter <= 'Z')
    {
        variable = letter;
    }
    else{
        throw std::invalid_argument(std::string(1, letter) + " can not be a variable");
    }
}

char ProductionRule::getVariable() const
{
    return variable;
}

void ProductionRule::changeVariable(char oldVariable, char newVariable)
{
    if(variable == oldVariable) 
    {
        variable = newVariable;
    }

    for (size_t i = 0; i < rules.size(); i++)
    {
        for (size_t j = 0; j < rules[i].size(); j++)
        {
            if(rules[i][j] == oldVariable)
            {
                rules[i][j] = newVariable;
            }
        }
        
    }
}

void ProductionRule::removeVariable(char letter)
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(std::find(rules[i].begin(), rules[i].end(), letter) != rules[i].end())
        {
            rules.erase(rules.begin() + i);
        }
    }
}

//rules
void ProductionRule::addRule(std::string rule) //validation
{
    rules.push_back(rule);
}

std::vector<std::string> ProductionRule::getRules() const
{
    return rules;
}

void ProductionRule::setRules(std::vector<std::string> newRules)
{
    for (size_t i = 0; i < newRules.size(); i++)
    {
        addRule(newRules[i]);
    }
}

bool ProductionRule::containsEpsilon() const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules[i] == "epsilon")
        {
            return true;
        }
    }
    return false;
}

bool ProductionRule::chomsky() const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        bool isSingleTerminal = rules[i].size()==1 && isTerminal(rules[i][0]);
        bool areTwoVariables = rules[i].size()==2 && isVariable(rules[i][0]) && isVariable(rules[i][1]);
        if(rules[i].size()>2)
        {
            if(rules[i] != "epsilon")
            {
                return false;
            }
            
        }
        else if (!isSingleTerminal && !areTwoVariables)
        {
            return false;
        }
    }
    return true;
}

void ProductionRule::display(std::ostream& out = std::cout) const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        out << " " <<rules[i];
    }
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

bool ProductionRule::isTerminal(char letter) const
{
    return ((letter >= '0' && letter <='9') || (letter >= 'a' && letter <='z'));
}

bool ProductionRule::isVariable(char letter) const
{
    return (letter >= 'A' && letter <='Z');
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

void ProductionRule::replaceNullable(std::vector<char>& nullableVariables)
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