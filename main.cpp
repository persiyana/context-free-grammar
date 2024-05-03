#include <iostream>

#include "./Engine/engine.hpp"

int main()
{
    std::string input;
    bool fileIsOpened = false;
    std::cin >> input;
    Engine engine;
    while(input != "exit")
    {
        if(input == "help")
        {
            engine.help();
        }
        else if(input == "open")
        {
            engine.open();
            fileIsOpened = true;
        }
        else if(input == "close" && fileIsOpened)
        {
            engine.close();
        }
        else if(input == "save" && fileIsOpened)
        {
            engine.save();
        }
        else if(input == "saveas" && fileIsOpened)
        {
            engine.saveAs();
        }
        else if(input == "list" && fileIsOpened)
        {
            engine.list();
        }
        else
        {
            std::cout << input <<" is invalid command" << std::endl;
        }
        std::cin >> input;
    }
    
    std::cout << "Exiting the program...";
}

