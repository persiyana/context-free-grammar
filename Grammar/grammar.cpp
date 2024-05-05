#include <iostream>
#include <fstream> 
#include <string> 
#include "grammar.hpp"

/*
unsigned Grammar::grammarsCount = 0;

Grammar::Grammar()
{
    grammarsCount++;
}

Grammar::~Grammar()
{
    grammarsCount--;
}
*/
void Grammar::setId(unsigned number)
{
    id = std::to_string(number+1);
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

void Grammar::print(std::ofstream& file)
{
    
    if (!file.is_open())
	{
		std::cerr << "File is not openG" << std::endl;
		return ;
	}

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

    file << std::endl << 's' << ' ' << start_variable;

    for (size_t i = 0; i < rules.size(); i++)
    {
        rules[i].print(file);
    }

    //file.close();
}

void Grammar::print()
{

    std::cout  << 'a';
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
            std::cout  << ' ' << symbol;
        }
    }

    std::cout  << std::endl << 'v';
    for (size_t i = 0; i < 26; i++)
    {
        if(variables[i] )
        {
            std::cout  << ' ' << (char)(i+'A');
        }
    }

    std::cout << std::endl << 's' << ' ' << start_variable;

    for (size_t i = 0; i < rules.size(); i++)
    {
        std::cout << std::endl <<"r"<< i; 
        rules[i].print();
    }
    std::cout << std::endl;
    //file.close();
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

bool Grammar::containsE()
{
    for (size_t i = 0; i < rules.size(); i++)
    {
       if(rules[i].containsE()){
        return true;
       }
    }
    return false;
}