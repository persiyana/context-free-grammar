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
            std::cout << "heheree";
            return false;
        }
    }

    return true;
}