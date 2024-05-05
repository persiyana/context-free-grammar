
#include "rule.hpp"

Rule::Rule(char variable, std::vector<std::string> rules)
:  variable(variable), rules(rules)
{}

void Rule::setVariable(char letter)
{
    if(letter >= 'A' && letter <= 'Z')
    {

        variable = letter;
    }
}

void Rule::addRule(std::string rule) //todo validation
{
    rules.push_back(rule);
}

void Rule::print(std::ofstream& file){

    if (!file.is_open())
	{
		std::cerr << "File is not openR" << std::endl;
		return ;
	}
    
    file << std::endl << "r " << variable;
    for (size_t i = 0; i < rules.size(); i++)
    {
        file<< " " <<rules[i];
    }

    //file.close();
}

void Rule::print(){

    std::cout << " " << variable;
    for (size_t i = 0; i < rules.size(); i++)
    {
        std::cout << " " <<rules[i];
    }

    //file.close();
}

bool Rule::containsE(){
    for (size_t i = 0; i < rules.size(); i++)
    {
        if(rules[i] == "e"){
            return true;
        }
    }
    return false;
    
}