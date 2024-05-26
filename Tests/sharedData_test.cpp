#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../libs/doctest.h"
#include "../SharedData/sharedData.hpp"
#include "../Grammar/grammar.hpp"

TEST_CASE("returns correct id")
{
    Grammar g1;
    g1.addLetterToTerminals('a');
    g1.addLetterToTerminals('b');
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');
    g1.addStartVariable('S');
    Grammar g2;
    g2.addLetterToTerminals('0');
    g2.addLetterToTerminals('1');
    g2.addLetterToVariables('R');
    g2.addLetterToVariables('M');
    g2.addStartVariable('M');

    SharedData::grammarList.push_back(g1);
    SharedData::grammarList.push_back(g2);

    std::cout << g1.getId();

    CHECK_EQ(SharedData::indexOfId(g1.getId()), 0);
    CHECK_EQ(SharedData::indexOfId(g2.getId()), 1);
}