#include <iostream>

#include "./Engine/engine.hpp"

int main()
{
    
    try
    {
        Engine& engine = Engine::getInstance();
        engine.run();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    catch (...) {
        std::cout << "Default Exception\n";
    }
}

