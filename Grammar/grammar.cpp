
#include "grammar.hpp"

void Grammar::addLetterToAlphabet(char letter)
{
    unsigned index = (unsigned)letter;
    if(letter >= 0 && letter <= 9)  
    {
        index -= 0;
        if(!this->alphabet[index]){
            this->alphabet[index] = true;
        }
    }
    if(letter >= 'a' && letter <= 'z')
    {
        index -= 'a';
        index += 10;

        if(!this->alphabet[index]){
            this->alphabet[index] = true;
        }
    }
}

void Grammar::addLetterToVariables(char letter)
{
    unsigned index = (unsigned) letter;
    if(letter >= 'A' && letter <= 'Z')
    {
        index -= 'A';

        if(!this->variables[index]){
            this->variables[index] = true;
        }
    }
}

void Grammar::addStartVariable(char letter)
{
    if(letter >= 'A' && letter <= 'Z')
    {
        start_variable = letter;
    }
}

void Grammar::addRule(const Rule& rule){
    rules.push_back(rule);
}

void Grammar::print(){
    for (size_t i = 0; i < 36; i++)
    {
        if(alphabet[i] ) std::cout << i << std::endl;
    }

    for (size_t i = 0; i < 26; i++)
    {
        if(variables[i] ) std::cout << i << std::endl;
    }

    std::cout << this->start_variable <<std::endl;

    for (size_t i = 0; i < rules.size(); i++)
    {
        rules[i].print();
    }
    
}