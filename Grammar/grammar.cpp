#include "grammar.hpp"

unsigned Grammar::grammarsCount = 0;


std::string Grammar::getId() const 
{
    return id;
}
void Grammar::setId()
{
    id = std::to_string(grammarsCount);
    for (size_t i = 0; i < 26; i++)
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
    for (size_t i = 0; i < 36; i++)
    {
        alphabet[i] = false;
        if(i<26){
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
		this->alphabet[letter - 'a' + 10] = true;
	}
}

void Grammar::addLetterToVariables(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
	{
		this->variables[letter - 'A'] = true;
	}
}

void Grammar::addStartVariable(char letter)
{
    grammarsCount++;
    setId(); 
    if(letter >= 'A' && letter <= 'Z')
    {
        start_variable = letter;
    }
}

void Grammar::addRule(const Rule& rule){
    rules.push_back(rule);
}

void Grammar::display(std::ostream& file) const
{

    file << 'a';
    for (size_t i = 0; i < 36; i++)
    {
        if(alphabet[i] )
        {
            char symbol;
            if(i<10)
            {
                symbol = i+'0';
            }
            else
            {
                symbol = i-10+'a';
            }
            file << ' ' << symbol;
        }
    }

    file << std::endl << 'v';
    for (size_t i = 0; i < 26; i++)
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

