#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../libs/doctest.h"
#include "../Engine/engine.hpp"

TEST_CASE("Singleton instance test")
{
    Engine& instance1 = Engine::getInstance();
    Engine& instance2 = Engine::getInstance();

    SUBCASE("Instances should be the same")
    {
        CHECK(&instance1 == &instance2);
    }
}