#include "grammar.hpp"

unsigned Grammar::grammarsCount = 0;

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

bool Grammar::getTerminal(size_t index) const
{
    return terminals[index];
}

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
            if(!HelperFunctions::contains<std::vector<char>, char>(nullableVariables, variable) && rules[i].isNullable(nullableVariables)) 
            {
                nullableVariables.push_back(variable);
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

void Grammar::addRule(const ProductionRule& rule){
    
    ProductionRule newRule;
    
    if(variables[rule.getVariable() - 'A'])
    {
        newRule.setVariable(rule.getVariable());
    }
    else
    {
        throw std::invalid_argument("This grammar does not contain variable " + std::string(1, rule.getVariable()) + "so this rule will not be added to the grammar");
    }

    std::vector<std::string> newProducts = rule.getRules();
    for (size_t i = 0; i < newProducts.size(); i++)
    {
        if(newProducts[i] == "epsilon" || productContainsValidData(newProducts[i]))
        {
            newRule.addRule(newProducts[i]);
        }
    }
    
    
    rules.push_back(rule);
}

void Grammar::removeRule(size_t index)
{
    
    if(rules.size() < index)
    {
        throw std::invalid_argument( "Grammar " + id + " does not contain rule with number " + std::string(1, index));
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

bool Grammar::hasRuleWith(char variable, char letter) const //example A -> a
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

void Grammar::chomskifyRules()
{
    eliminateEpsilonProduction();
    eliminateUnitProduction();
    eliminateUselessProduction();
    replaceTerminals();
    convertToTwoVariabless();

    setId();
}

// if a rule have an epsilon production and it is not the start symbol, then removes it
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

// the productions of type ‘A -> B’ are called unit productions and if we want to remove them, then we must replace 'B' with its own productions
// if we have rules 'X -> Y' and 'Y -> a' then the grammar without useless procudtion will be 'X -> a'
void Grammar::eliminateUnitProduction()
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        std::vector<std::string> ruleOfI = rules[i].getRules();

        for (size_t j = 0; j < ruleOfI.size(); j++)
        {
            std::string currentRule = ruleOfI[j];

            if(currentRule.size() == 1 && rules[i].isVariable(currentRule[0]))
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
                    //finds the rule in wich the variable is the unit production of ruleOfI[j] 
                    while(rules[indexOfVar].getVariable() != variable && indexOfVar < rules.size())
                    {
                        indexOfVar++;
                    }
                    if(indexOfVar < rules.size())
                    {
                        //adds the products of the variable of the unit poduction to ruleOfI[j] and removes the unit production
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

// remove each production that can never take part in the derivation of any string
void Grammar::eliminateUselessProduction()
{
    size_t prev_size = 0;

    // removes rules that can never terminate
    // for example removes B -> aB | Bb
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
                if(HelperFunctions::contains<std::string, char>(rulesOfI[j], variableOfI))
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

    // adds to unreachableVariables all variables except the start one
    for (size_t i = 0; i < VARIABLES_SIZE; i++)
    {
        char variable = i+'A';
        if(variables[i] && variable!=start_variable)
        {
            unreachableVariables.push_back(variable);
        }
    }
    
    
    //removes all reachable variables from the unreachableVariable array
    prev_size = 0;
    do
    {
        prev_size = unreachableVariables.size();
        for (size_t i = 0; i < rules.size(); i++)
        {
            if(!HelperFunctions::contains<std::vector<char>, char>(unreachableVariables, rules[i].getVariable()))
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


    //removes unreachable variables
    for (size_t i = 0; i < unreachableVariables.size(); i++)
    {
        variables[unreachableVariables[i]-'A'] = false;
        removeVariable(unreachableVariables[i]);
    }
    
}

// for each rule if one of the productions contains terminal and the length of that production is not 1 then create a new rule
// production rule X->xY can be decomposed as: 
//      X->ZY    
//      Z->x
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
                    if(rules[i].isTerminal(ruleOfI[j][k]))
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

// for each rule if one of the productions has more than two variables then create a new rule 
// production rule X->XYZ can be decomposed as: 
//      X->PZ    
//      P->XY
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
                    if(rules[i].isVariable(ruleOfI[j][k]) && rules[i].isVariable(ruleOfI[j][k+1]))
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

bool Grammar::productContainsValidData(const std::string &product)
{
    for (size_t i = 0; i < product.size(); i++)
    {
        bool isValidVariable = product[i] >= 'A' && product[i]<= 'Z' && variables[product[i]-'A'];
        bool isValidTerminalLetter = product[i] >= 'a' && product[i]<= 'z' && terminals[product[i]-'a'+DIGITS_COUNT];
        bool isValidTerminalDigit = product[i] >= '0' && product[i]<= '9' && terminals[product[i]-'0'];
        if(!isValidTerminalDigit || !isValidTerminalLetter || !isValidVariable)
        {
            return false;
        }
    }
    return true;
}

void Grammar::display(std::ostream& file) const
{

    file << 't';
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
    std::vector<std::vector<std::string>> table(n, std::vector<std::string> (n, initalValue));

    //for each variable A, we check if there is a rule A -> word[i] and if it is so then we push back the variable into the table in position ii
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
               // for each rule A -> BC we check if (i, k) cell contains B and (k + 1, j) cell contains C
               // if so, we put A in cell (i, j) of our table.
               for (size_t ruleIndex = 0; ruleIndex < rules.size(); ruleIndex++)
               {
                    std::vector<std::string> rulesOfVar = rules[ruleIndex].getRules();
                    for (size_t t = 0; t < rulesOfVar.size(); t++)
                    {
                        if(rulesOfVar[t].size() == 2)
                        {
                            if(HelperFunctions::contains<std::string, char>(table[i][k], rulesOfVar[t][0]) 
                                && HelperFunctions::contains<std::string, char>(table[k+1][j], rulesOfVar[t][1]) 
                                && !HelperFunctions::contains<std::string, char>(table[i][j], rules[ruleIndex].getVariable()))
                            {
                                table[i][j].push_back(rules[ruleIndex].getVariable());
                            }
                        }
                    }
                    
               }
               
            }
            
        }
    }

    // if the start variable is in table[0][n-1] then the grammar recognizes the word
    return HelperFunctions::contains<std::string, char>(table[0][n-1], start_variable);
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


