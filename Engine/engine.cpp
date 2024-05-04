#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "engine.hpp"

Engine::Engine(std::string fileDirectory) //mai mi trqbva samo default
: fileDirectory(fileDirectory){
    fileName = getFileNameFromDir(fileDirectory);
}

std::string Engine::getFileNameFromDir(std::string fileDir){
    std::string temp = "";
    for (size_t i = 0; i < fileDir.length(); i++)
    {
        if(fileDir[i] == '\\'){
            temp = "";
        }
        else{
            temp.push_back(fileDir[i]);
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
	
    fileName = getFileNameFromDir(fileDirectory);

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
            currentGrammar.setId(grammarList.size());
            grammarList.push_back(currentGrammar);
            currentGrammar.clear();
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

void Engine::close()
{
    fileDirectory = "";
    grammarList.clear();
    std::cout << "Succesfully closed " << fileName << std::endl;
    fileName = "";
}

void Engine::save()
{
    std::string grammar;
    std::getline(std::cin, grammar);
    if(grammar.length() == 0)
    {
       std::ofstream file(fileDirectory);
        print(file);
        file.close();
        std::cout << "Successfully saved" << std::endl; 
    }
    else
    {
        saveGrammar(grammar);
    }
}

void Engine::saveGrammar(std::string idAndFile)
{
    std::vector<std::string> arr = split(idAndFile);
    std::string searchedId = arr[0];
    size_t i = 0;
    while ( i < grammarList.size() && grammarList[i].getId()!=searchedId)
    {
        i++;
    }
    
    if(i == grammarList.size() && grammarList[i].getId()!=searchedId) 
    {
        std::cout << "Id not found" << std::endl;
    }

    else{
        std::string fileDir;
        for (size_t i = 1; i < arr.size()-1; i++)
        {
           fileDir +=(arr[i] +' ');
        }
        fileDir+=arr[arr.size()-1];

        std::ofstream file(fileDir);
        grammarList[i].print(file);
    }
}

void Engine::saveAs()
{
    std::string newFile;
    std::cin >> newFile;
    std::ofstream file(newFile);
    print(file);
    file.close();
    std::cout << "Successfully saved another " << getFileNameFromDir(newFile) << std::endl;
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

void Engine::print(std::ofstream& file)
{
    if (!file.is_open())
	{
		std::cerr << "File is not openE" << std::endl;
		return ;
	}

    for (size_t i = 0; i < grammarList.size(); i++)
    {
        grammarList[i].print(file);
        file << std::endl << ";" << std::endl;
    }
   
    file.close();
}

void Engine::list()
{
    for (size_t i = 0; i < grammarList.size(); i++)
    {
        std::cout << grammarList[i].getId() << std::endl;
    }
    
}

void Engine::print()
{
    std::string searchedId;
    std::cin >> searchedId;
    size_t i = 0;
    while ( i < grammarList.size() && grammarList[i].getId()!=searchedId)
    {
        i++;
    }
    
    if(i == grammarList.size() && grammarList[i].getId()!=searchedId) 
    {
        std::cout << "Id not found" << std::endl;
    }
    else
    {
        //todo grammarList[i].print();
    }
}