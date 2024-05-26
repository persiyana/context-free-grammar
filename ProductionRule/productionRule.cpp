#include "productionRule.hpp"

ProductionRule::ProductionRule(char letter, const std::vector<std::string>&  initialRules)
{
    setVariable(letter);
    setRules(initialRules);
}

ProductionRule::ProductionRule(char letter, char rule)
{
    setVariable(letter);
    addRule(std::string(1, rule));
}

ProductionRule::ProductionRule(char letter, const std::string& rule)
{
    setVariable(letter);
    addRule(rule);
}

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
            if(rules[i][j] == oldVariable && rules[i] != "epsilon")
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
        if(rules[i] == std::string(1, letter))
        {
            rules.erase(rules.begin() + i);
        }
        for (size_t j = 0; j < rules[i].size(); j++)
        {
           if(rules[i][j]==letter)
           {
                rules[i].erase(rules[i].begin() +j);
           }
        }
    }
}

void ProductionRule::addRule(const std::string& rule)
{
    rules.push_back(rule);
}

std::vector<std::string> ProductionRule::getRules() const
{
    return rules;
}

void ProductionRule::setRules(const std::vector<std::string>& newRules)
{
    for (size_t i = 0; i < newRules.size(); i++)
    {
        if(!HelperFunctions::contains<std::vector<std::string>, std::string>(rules, newRules[i]))
        {
            addRule(newRules[i]);
        }
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

void ProductionRule::display(std::ostream& out) const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        out << " " <<rules[i];
    }
}

bool ProductionRule::hasLetterAsProduct(char letter) const //rule with only letter // X -> letter
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

bool ProductionRule::isNullable(const std::vector<char>& nullableVariables) const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if (rules[i] == "epsilon")
        {
            return true;
        }

        bool allNullable = true;

        //check whether all of the chars of the rule are nullable variables
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

void ProductionRule::replaceNullable(const std::vector<char>& nullableVariables)
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
                // if rules[i][j] is nullable variable then replace it with a permutation of rules[i] 
                // if S -> ABCd and A, B and C are nullable, then the rule will become S -> ABCd | ABd | ACd | BCd | Ad  |  Bd  |Cd | d
                if(HelperFunctions::contains<std::vector<char>, char> (nullableVariables, rules[i][j]))
                {
                    std::string newProductionRule = rules[i];
                    newProductionRule.erase(newProductionRule.begin()+j);
                    if(!HelperFunctions::contains<std::vector<std::string>, std::string>(rules, newProductionRule)) //does not contain
                    {
                        rules.push_back(newProductionRule);
                    }
                    
                }
            }           
        }
    }
}