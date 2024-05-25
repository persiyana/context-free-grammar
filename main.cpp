#include <iostream>

#include "./Engine/engine.hpp"

int main()
{
    
    try
    {
        Engine engine;
        engine.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (...) {
        std::cout << "Default Exception\n";
    }
}

