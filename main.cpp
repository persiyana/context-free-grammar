#include <iostream>

#include "./Engine/engine.hpp"

int main()
{
    Engine& engine = Engine::getInstance();
    engine.run();
   
    return 0;
}
