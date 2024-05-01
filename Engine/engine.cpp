#include <iostream>
#include <fstream>
#include <string>

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

void Engine::open()
{
    std::cin >> fileDirectory;
    fileName = getFileNameFromDir();

    std::ifstream file(fileDirectory);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << fileName << std::endl;
    }

    std::cout << "Successfully opened " << fileName << std::endl;
    
    std::string line;

    while(std::getline(file, line)){
        std::cout << line << std::endl;
    }
    
    file.close();
    
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