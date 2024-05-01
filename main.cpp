#include <iostream>

#include "./Engine/engine.hpp"

int main()
{
    std::string input;
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
        }
        std::cin >> input;
    }
    
    std::cout << "Exiting the program...";
}

