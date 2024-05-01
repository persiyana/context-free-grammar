#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "engine.hpp"

Engine::Engine(std::string fileDirectory) //mai mi trqbva samo default
: fileDirectory(fileDirectory){
    fileName = getFileNameFromDir();
}

std::string Engine::getFileNameFromDir(){
    std::string temp = "";
    for (size_t i = 0; i < fileDirectory.length(); i++)
    {
        if(fileDirectory[i] == '\\'){
            temp = "";
        }
        else{
            temp.push_back(fileDirectory[i]);
        }
    }
    return temp;
}


std::vector<std::string> Engine::split(std::string line)
{
    std::vector<std::string> result;

    std::stringstream ss;
    ss << line;
    
    std::string temp;
    while(std::getline(ss, temp, ' '))
    {
        result.push_back(temp);
    }

    return result;
}

void Engine::open()
{
    std::cin.ignore();

    std::getline(std::cin, fileDirectory);
	
    fileName = getFileNameFromDir();

    std::ifstream file(fileDirectory);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    std::cout << "Successfully opened " << fileName << std::endl;
    
    std::string line;
    Grammar currentGrammar;

    while(std::getline(file, line)){
        
        std::vector<std::string> lineVector = split(line);
        if(lineVector[0] == ";")
        {
            grammarList.push_back(currentGrammar);
            Grammar newG;
            currentGrammar = newG;
        }
        else if(lineVector[0] == "a")
        {
            for (size_t i = 1; i < lineVector.size(); i++)
            {
                if(lineVector[i].length() == 1){
                    currentGrammar.addLetterToAlphabet(lineVector[i][0]);
                }
                
            }
        }
        else if(lineVector[0] == "v")
        {
            for (size_t i = 1; i < lineVector.size(); i++)
            {
                if(lineVector[i].length() == 1){
                    currentGrammar.addLetterToVariables(lineVector[i][0]);
                }
                
            }
        }
        else if(lineVector[0] == "s")
        {
            if(lineVector[1].length() == 1){
                currentGrammar.addStartVariable(lineVector[1][0]);
            }
        }

        else if(lineVector[0] == "r")
        {
            Rule currentRule;
            if(lineVector[1].length() == 1){
                currentRule.setVariable(lineVector[1][0]);
            }
            if(currentRule.getVariable() != '\0')
            {
                for (size_t i = 2; i < lineVector.size(); i++)
                {
                    currentRule.addRule(lineVector[i]);
                }
                
            }
            currentGrammar.addRule(currentRule);
        }
    }
    
    file.close();

    //print();
}

void Engine::help()
{
    std::cout << "The following commands are supported:" <<
    std::endl << "open <file>           opens <file>" <<
    std::endl << "close                 closes currently opened file" << 
    std::endl << "save                  saves the currently open file" << 
    std::endl << "saveas <file>         saves the currently open file in <file>" << 
    std::endl << "help                  prints this information" << 
    std::endl << "exit                  exists the program" << 
    std::endl << "list                  sth" << 
    std::endl << "print <id>            sth" << 
    std::endl << "save <id> <filename>  sth" << 
    std::endl << "addRule <id> <rule>   sth" << 
    std::endl << "removeRule <id> <n>   sth" << 
    std::endl << "union <id1> <id2>     sth" << 
    std::endl << "concat <id1> <id2>    sth" << 
    std::endl << "chomsky <id>          sth" << 
    std::endl << "cyk <id>              sth" << 
    std::endl << "iter <id>             sth" << 
    std::endl << "empty <id>            sth" << 
    std::endl << "chomskify <id>        sth" << std::endl;
}

void Engine::print()
{
    for (size_t i = 0; i < grammarList.size(); i++)
    {
        grammarList[i].print();
        std::cout << "Next:" <<std::endl;
    }
   
}