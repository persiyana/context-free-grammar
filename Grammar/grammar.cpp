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

void Grammar::clear()
{
    id = "";
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        alphabet[i] = false;
        if(i<VARIABLES_SIZE){
            variables[i] = false;
        }
    }
    start_variable = '\0';
    rules.clear();
}

void Grammar::addLetterToAlphabet(char letter)
{
    if (letter >= '0' && letter <= '9')
	{
		this->alphabet[letter - '0'] = true;
	}
	else if (letter >= 'a' && letter <= 'z')
	{
		this->alphabet[letter - 'a' + DIGITS_COUNT] = true;
	}
}

void Grammar::addLetterToAlphabet(size_t index)
{
    this->alphabet[index] = true;
}

void Grammar::addLetterToVariables(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
	{
		this->variables[letter - 'A'] = true;
	}
}

void Grammar::addLetterToVariables(size_t index)
{
    this->variables[index] = true;
}

void Grammar::addStartVariable(char letter)
{
    grammarsCount++;
   
    if(letter >= 'A' && letter <= 'Z')
    {
        start_variable = letter;
        addLetterToVariables(letter);
    } 
    
    setId(); 
}

void Grammar::addRule(const Rule& rule){
    rules.push_back(rule);
}

void Grammar::display(std::ostream& file) const
{

    file << 'a';
    for (size_t i = 0; i < ALPHABET_SIZE; i++)
    {
        if(alphabet[i] )
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

void Grammar::removeRule(size_t index)
{
    
    if(rules.size() < index)
    {
        std::cout << "Grammar " << id << " does not contain rule " << index <<std::endl;
    }
    else
    {
        rules.erase(rules.begin() + index);
    }
}

bool Grammar::containsE() const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
       if(rules[i].containsE()){
        return true;
       }
    }
    return false;
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

char Grammar::getStartVariable() const
{
    return start_variable;
}

bool Grammar::getVariable(size_t i) const
{
    return variables[i];
}

bool Grammar::getAlphabet(size_t i) const
{
    return alphabet[i];
}

std::vector<Rule> Grammar::getRules() const
{
    return rules;
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

bool Grammar::chomsky() const
{
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(start_variable != rules[i].getVariable() && rules[i].containsE())
        {
            
            return false;
        }
        if(!rules[i].otherRules())
        {
            return false;
        }
    }

    return true;
}

bool Grammar::hasRule(char variable, char letter) const
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

bool Grammar::stringContainsChar(std::string str, char ch) const
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if(str[i]==ch)
        {
            return true;
        }
    }
    return false;
}

bool Grammar::cyk(const std::string& word) const
{
   
    size_t n = word.size();
    if(n==0)
    {
        for (size_t i = 0; i < rules.size(); i++)
        {
            if(start_variable == rules[i].getVariable() && rules[i].containsE())
            {
                return true;
            }
        }
        return false;
    } 

    std::string initalValue = "";
    std::vector<std::vector<std::string> > table(n, std::vector<std::string> (n, initalValue));

    /*for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < VARIABLES_SIZE; j++)
        {
            if(variables[j])
            {
                char variable = variables[j]+'A';
                if(hasRule(variable, word[i]))
                {
                    table[i][i].push_back(variable);
                }
            }
        }
        
    }

    for (size_t i = 0; i < n; i++)
   {
    for (size_t j = 0; j < n; j++)
   {
        std::cout << table[i][j] << '\t';
   }
   std::cout<<std::endl;
   }

    for (size_t l = 1; l < n; l++)
    {
        for (size_t i = 0; i < n-l; i++)
        {
            size_t j = i+l;
            for (size_t k = i; k < j-1; k++)
            {
               for (size_t ruleIndex = 0; ruleIndex < rules.size(); ruleIndex++)
               {
                    std::vector<std::string> rulesOfVar = rules[ruleIndex].getRules();
                    for (size_t t = 0; t < rulesOfVar.size(); t++)
                    {
                        if(rulesOfVar[t].size() == 2)
                        {
                            if(stringContainsChar(table[i][k], rulesOfVar[t][0]) && stringContainsChar(table[k+1][j], rulesOfVar[t][1]))
                            {
                                table[i][j].push_back(rules[ruleIndex].getVariable());
                            }
                        }
                    }
                    
               }
               
            }
            
        }
        
    }*/
    
   
   

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