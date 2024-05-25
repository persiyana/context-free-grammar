#include "grammar.hpp"

unsigned Grammar::grammarsCount = 0;

//id
std::string Grammar::getId() const 
{
    return id;
}

void Grammar::setId()
{
    id = std::to_string(grammarsCount);
    for (size_t i = 0; i < VARIABLES_SIZE; i++)
    {
        if(variables[i])
        {   
            id += (i+'A');
        }
    }
}

//terminals
void Grammar::addLetterToTerminals(char letter)
{
    if (letter >= '0' && letter <= '9')
	{
		this->terminals[letter - '0'] = true;
	}
	else if (letter >= 'a' && letter <= 'z')
	{
		this->terminals[letter - 'a' + DIGITS_COUNT] = true;
	}
    else 
    {
        throw std::invalid_argument(letter + " is not a valid terminal");
    }
}

void Grammar::addLetterToTerminals(size_t index)
{
    this->terminals[index] = true;
}

bool Grammar::isOfTerminals(char letter)
{
    return ((letter>='a' && letter<='z') || (letter>='0' && letter<='9'));
}

bool Grammar::getTerminal(size_t index) const
{
    return terminals[index];
}

//variables
void Grammar::addLetterToVariables(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
	{
		this->variables[letter - 'A'] = true;
	}
    else 
    {
        throw std::invalid_argument(letter + " is not a valid variable");
    }
}

void Grammar::addLetterToVariables(size_t index)
{
    this->variables[index] = true;
}

bool Grammar::isOfVariables(char letter)
{
    return (letter>='A' && letter<='Z');
}

void Grammar::removeVariable(char variable)
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules[i].getVariable() == variable)
        {
            rules.erase(rules.begin() + i);
            i--;
        }
        else
        {
            rules[i].removeVariable(variable); 
        }
    }
    
}

void Grammar::getNullableVariables(std::vector<char>& nullableVariables) const
{
    size_t previous_size = 0;
    do
    {
        previous_size = nullableVariables.size();

        for (size_t i = 0; i < rules.size(); i++)
        {
            char variable = rules[i].getVariable();
            if (std::find(nullableVariables.begin(), nullableVariables.end(), variable) == nullableVariables.end()) {
                if (rules[i].isNullable(nullableVariables)) {
                    nullableVariables.push_back(variable);
                }
            }
        }
        

    } while (nullableVariables.size() != previous_size);
    
}

char Grammar::getVariableForRule(const std::string& rule)
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        std::vector<std::string> ruleOfI = rules[i].getRules();
        if(ruleOfI.size()==1 && ruleOfI[0].size() == rule.size() && ruleOfI[0]==rule){
            return rules[i].getVariable();
        }
    }
    return ' ';
}

char Grammar::getUnusedVariable() const
{
    for (size_t i = 0; i < VARIABLES_SIZE; i++)
    {
        if(!variables[i])
        {
            return i + 'A';
        }
    }
    return ' ';
}

bool Grammar::getVariable(size_t index) const
{
    return variables[index];
}

void Grammar::changeVariable(size_t letter, size_t unusedLetter)
{
    variables[letter]= false;
    variables[unusedLetter] = true;
    char oldVar = letter+'A';
    char newVar = unusedLetter + 'A';
    for (size_t i = 0; i < rules.size(); i++)
    {
        rules[i].changeVariable(oldVar, newVar);
    }
    for (size_t i = 0; i < id.size(); i++)
    {
        if(id[i] == oldVar)
        {
            id[i] = newVar;
        }
    }
    
}

//start variable
void Grammar::addStartVariable(char letter)
{
    grammarsCount++;
   
    if(letter >= 'A' && letter <= 'Z')
    {
        start_variable = letter;
        addLetterToVariables(letter);
    } 
    else
    {
        throw std::invalid_argument(letter + " is not a variable, so it cannot be a start variable");
    }
    
    setId(); 
}

char Grammar::getStartVariable() const
{
    return start_variable;
}

//rules
void Grammar::addRule(const ProductionRule& rule){
    rules.push_back(rule);
}

void Grammar::removeRule(size_t index)
{
    
    if(rules.size() < index)
    {
        throw std::invalid_argument( "Grammar " + id + " does not contain rule " + std::string(1, index));
    }
    else
    {
        rules.erase(rules.begin() + index);
    }
}

bool Grammar::containsEpsilon() const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
       if(rules[i].containsEpsilon()){
        return true;
       }
    }
    return false;
}

std::vector<ProductionRule> Grammar::getRules() const
{
    return rules;
}

bool Grammar::hasRuleWith(char variable, char letter) const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules[i].getVariable() == variable)
        {
            return rules[i].hasLetter(letter);
        }
    }
    return false;
}

//chomsky normal form

void Grammar::chomskifyRules()
{
    eliminateEpsilonProduction();
    eliminateUnitProduction();
    eliminateUselessProduction();
    replaceTerminals();
    convertToTwoVariabless();

    setId();
}

void Grammar::eliminateUselessProduction()
{
    size_t prev_size = 0;

    do
    {
        prev_size = rules.size();
        for (size_t i = 0; i < rules.size(); i++)
        {
            std::vector<std::string> rulesOfI = rules[i].getRules();
            char variableOfI = rules[i].getVariable();
            size_t count = 0;
            for (size_t j = 0; j < rulesOfI.size(); j++)
            {
                if(std::find(rulesOfI[j].begin(), rulesOfI[j].end(), variableOfI) != rulesOfI[j].end())
                {
                    count++;
                }
                
            }
            
            
            if(count == rulesOfI.size() )
            {
                variables[variableOfI-'A'] = false;
                removeVariable(variableOfI);
            }

        }
    } while (prev_size != rules.size());
    
    
    std::vector<char> unreachableVariables;

    for (size_t i = 0; i < VARIABLES_SIZE; i++)
    {
        char variable = i+'A';
        if(variables[i] && variable!=start_variable)
        {
            unreachableVariables.push_back(variable);
        }
    }
    
    
    prev_size = 0;
    do
    {
        prev_size = unreachableVariables.size();
        for (size_t i = 0; i < rules.size(); i++)
        {
            if(std::find(unreachableVariables.begin(), unreachableVariables.end(), rules[i].getVariable()) == unreachableVariables.end())
            {
                std::vector<std::string> rulesOfI = rules[i].getRules();
                for (size_t j = 0; j < rulesOfI.size(); j++)
                {
                    std::string rule = rulesOfI[j];
                    for (size_t k = 0; k < rule.size(); k++)
                    {
                        for (size_t m = 0; m < unreachableVariables.size(); m++)
                        {
                            if(rule[k] ==unreachableVariables[m])
                            {
                                unreachableVariables.erase(unreachableVariables.begin() + m);
                            }
                        }
                        
                    }
                    
                }
                
            }

        }
    } while (prev_size != unreachableVariables.size());


    for (size_t i = 0; i < unreachableVariables.size(); i++)
    {
        variables[unreachableVariables[i]-'A'] = false;
        removeVariable(unreachableVariables[i]);
    }
    
}

void Grammar::eliminateEpsilonProduction()
{
    std::vector<char> nullableVariables;
    getNullableVariables(nullableVariables);
    for (int i = 0; i < rules.size(); i++)
    {
        if(rules[i].getRules().size() == 1 && rules[i].getRules()[0] == "epsilon")
        {
            rules.erase(rules.begin() + i);
            i--;
        }
        else
        {
            rules[i].replaceNullable(nullableVariables);
        }
    }
    
}

void Grammar::eliminateUnitProduction()
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        std::vector<std::string> ruleOfI = rules[i].getRules();

        for (size_t j = 0; j < ruleOfI.size(); j++)
        {
            std::string currentRule = ruleOfI[j];

            if(currentRule.size() == 1 && isOfVariables(currentRule[0]))
            {
                if(currentRule[0] == rules[i].getVariable())
                {
                    ruleOfI.erase(ruleOfI.begin()+j);
                    j--;
                }
                else
                {
                    char variable = ruleOfI[j][0];
                    int indexOfVar = 0;
                    while(rules[indexOfVar].getVariable() != variable && indexOfVar < rules.size())
                    {
                        indexOfVar++;
                    }
                    if(indexOfVar < rules.size())
                    {
                        std::vector<std::string> rulesOfVar = rules[indexOfVar].getRules();
                        ruleOfI.erase(ruleOfI.begin()+j);
                        for (size_t k = 0; k < rulesOfVar.size(); k++)
                        {
                            ruleOfI.push_back(rulesOfVar[k]);
                        }
                        
                    }
                }
            }
        }

        rules[i].setRules(ruleOfI);
    }
    
}

void Grammar::replaceTerminals()
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        std::vector<std::string> ruleOfI = rules[i].getRules();
        for (size_t j = 0; j < ruleOfI.size(); j++)
        {
            if(ruleOfI[j].size() > 1 && ruleOfI[j] != "epsilon")
            {
                for (size_t k = 0; k < ruleOfI[j].size(); k++)
                {
                    if(isOfTerminals(ruleOfI[j][k]))
                    {
                        std::string temp;
                        temp+= ruleOfI[j][k];
                        char variable = getVariableForRule(temp);
                        if(variable==' '){
                            variable = getUnusedVariable();
                            addLetterToVariables(variable);
                            ProductionRule newRule(variable, ruleOfI[j][k]);
                            rules.push_back(newRule);
                        }
                        ruleOfI[j][k]=variable;
                    }
                }
                
            }
        }
        rules[i].setRules(ruleOfI);
    }
    
}

void Grammar::convertToTwoVariabless()
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        std::vector<std::string> ruleOfI = rules[i].getRules();
        for (size_t j = 0; j < ruleOfI.size(); j++)
        {
            if(ruleOfI[j].size() > 2)
            {
                for (size_t k = 0; k < ruleOfI[j].size()-1; k++)
                {
                    if(isOfVariables(ruleOfI[j][k]) && isOfVariables(ruleOfI[j][k+1]))
                    {
                        std::string newR = "";
                        newR.push_back(ruleOfI[j][k]);
                        newR.push_back(ruleOfI[j][k+1]);
                        char variable = getVariableForRule(newR);
                        if(variable==' '){
                            variable = getUnusedVariable();
                            addLetterToVariables(variable);
                            ProductionRule newRule(variable, newR);
                            rules.push_back(newRule);
                            
                        }
                        ruleOfI[j][k]=variable;
                        for (size_t m = k+1; m < ruleOfI[j].size()-1; m++)
                        {
                            ruleOfI[j][m] = ruleOfI[j][m+1];
                        }
                        ruleOfI[j].pop_back();
                    }
                }
            }
        }
        rules[i].setRules(ruleOfI);
    }
    
}

//everything
void Grammar::display(std::ostream& file) const
{

    file << 'a';
    for (size_t i = 0; i < TERMINALS_SIZE; i++)
    {
        if(terminals[i] )
        {
            char symbol;
            if(i<DIGITS_COUNT)
            {
                symbol = i+'0';
            }
            else
            {
                symbol = i-DIGITS_COUNT+'a';
            }
            file << ' ' << symbol;
        }
    }

    file << std::endl << 'v';
    for (size_t i = 0; i < VARIABLES_SIZE; i++)
    {
        if(variables[i] )
        {
            file << ' ' << (char)(i+'A');
        }
    }

    file << std::endl << 's' << ' ' << start_variable ;

    for (size_t i = 0; i < rules.size(); i++)
    {
        file << std::endl << 'r' << i << " " << rules[i].getVariable();
        rules[i].display(file);
    }
}

bool Grammar::chomsky() const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(start_variable != rules[i].getVariable() && rules[i].containsEpsilon())
        {
            return false;
        }
        if(!rules[i].chomsky())
        {
            return false;
        }
    }

    return true;
}

bool Grammar::cyk(const std::string& word) const
{
   
    size_t n = word.size();
    if(n==0)
    {
        for (size_t i = 0; i < rules.size(); i++)
        {
            if(start_variable == rules[i].getVariable() && rules[i].containsEpsilon())
            {
                return true;
            }
        }
        return false;
    } 

    std::string initalValue = "";
    std::vector<std::vector<std::string> > table(n, std::vector<std::string> (n, initalValue));

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < VARIABLES_SIZE; j++)
        {
            if(variables[j])
            {
                char variable = j+'A';
                if(hasRuleWith(variable, word[i]))
                {
                    table[i][i].push_back(variable);
                }
            }
        }
        
    }

    for (size_t l = 1; l < n; l++)
    {
        for (size_t i = 0; i < n-l; i++)
        {
            size_t j = i+l;
            for (size_t k = i; k < j; k++)
            {
               for (size_t ruleIndex = 0; ruleIndex < rules.size(); ruleIndex++)
               {
                    std::vector<std::string> rulesOfVar = rules[ruleIndex].getRules();
                    for (size_t t = 0; t < rulesOfVar.size(); t++)
                    {
                        if(rulesOfVar[t].size() == 2)
                        {
                            if(HelperFunctions::contains(table[i][k], rulesOfVar[t][0]) 
                                && HelperFunctions::contains(table[k+1][j], rulesOfVar[t][1]) 
                                && !HelperFunctions::contains(table[i][j], rules[ruleIndex].getVariable()))
                            {
                                table[i][j].push_back(rules[ruleIndex].getVariable());
                            }
                        }
                    }
                    
               }
               
            }
            
        }
    }

    std::string res = table[0][n-1];
    for (size_t i = 0; i < res.size(); i++)
    {
        if(res[i]==start_variable)
        {
            return true;
        }
    }
    return false;
}

bool Grammar::isEmpty() const
{
    Grammar temp = *this;
    temp.eliminateUselessProduction();
    
    std::vector<ProductionRule> tempRules = temp.getRules();

    for (size_t i = 0; i < tempRules.size(); i++)
    {
        if(tempRules[i].getVariable() == temp.getStartVariable())
        {
            return false;
        }
    }
    return true;
}

void Grammar::clear()
{
    id = "";
    for (size_t i = 0; i < TERMINALS_SIZE; i++)
    {
        terminals[i] = false;
        if(i<VARIABLES_SIZE){
            variables[i] = false;
        }
    }
    start_variable = '\0';
    rules.clear();
}


