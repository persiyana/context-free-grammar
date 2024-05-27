#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../libs/doctest.h"
#include "../Grammar/grammar.hpp"
#include "../ProductionRule/productionRule.hpp"

TEST_CASE("Properly adds letter to terminals")
{
    Grammar g1;
    SUBCASE("addLetterToTerminals(char letter)")
    {
        g1.addLetterToTerminals('a');
        CHECK(g1.getTerminal('a'-'a'+10));
    }
    SUBCASE("addLetterToTerminals(char letter) with invalid data")
    {
        CHECK_THROWS_AS(g1.addLetterToTerminals('A'), std::invalid_argument);
    }
    SUBCASE("addLetterToTerminals(size_t index)")
    {
        size_t index = 10;
        g1.addLetterToTerminals(index);
        CHECK(g1.getTerminal('a'-'a'+10));
    }
}

TEST_CASE("Properly adds letter to variables")
{
    Grammar g1;
    SUBCASE("addLetterToTerminals(char letter)")
    {
        g1.addLetterToVariables('A');
        CHECK(g1.getVariable('A'-'A'));
    }
    SUBCASE("addLetterToTerminals(char letter) with invalid data")
    {
        CHECK_THROWS_AS(g1.addLetterToVariables('a'), std::invalid_argument);
    }
    SUBCASE("addLetterToTerminals(size_t index)")
    {
        size_t index = 0;
        g1.addLetterToVariables(index);
        CHECK(g1.getVariable('A'-'A'));
    }
}

TEST_CASE("getUnusedVariable")
{
    Grammar g1;
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');

    CHECK_EQ(g1.getUnusedVariable(), 'A');
}

TEST_CASE("changeVariable")
{
    Grammar g1;
    g1.addLetterToTerminals('a');
    g1.addLetterToTerminals('b');
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');
    g1.addStartVariable('S');
    ProductionRule g11('S', std::vector<std::string>{"aSb", "XX", "epsilon"});
    ProductionRule g12('X', std::vector<std::string>{"bbXa", "S"});
    g1.addRule(g11);
    g1.addRule(g12);

    g1.changeVariable('S'-'A', 'P'-'A');
    CHECK_EQ(g1.getStartVariable(), 'P');
    std::vector<ProductionRule> rule = g1.getRules();
    std::string product = rule[0].getRules()[0];
    CHECK_EQ(product, "aPb");
}

TEST_CASE("Properly adds start variable")
{
    Grammar g1;
    g1.addStartVariable('S');
    CHECK_EQ(g1.getStartVariable(), 'S');
    CHECK_EQ(g1.getId(), "2S");
}

TEST_CASE("addRule")
{
    Grammar g1;
    g1.addLetterToTerminals('a');
    g1.addLetterToTerminals('b');
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');
    g1.addStartVariable('S');
    ProductionRule g11('S', std::vector<std::string>{"aSb", "XX", "epsilon"});
    ProductionRule g12('X', std::vector<std::string>{"bbXa", "S"});
    g1.addRule(g11);
    g1.addRule(g12);

    std::vector<ProductionRule> rule = g1.getRules();

    std::string product = rule[0].getRules()[0];
    CHECK_EQ(product, "aSb");
}


TEST_CASE("removeRule")
{
    Grammar g1;
    g1.addLetterToTerminals('a');
    g1.addLetterToTerminals('b');
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');
    g1.addStartVariable('S');
    ProductionRule g11('S', std::vector<std::string>{"aSb", "XX", "epsilon"});
    ProductionRule g12('X', std::vector<std::string>{"bbXa", "S"});
    g1.addRule(g11);
    g1.addRule(g12);
    g1.removeRule(0);

    std::vector<ProductionRule> rule = g1.getRules();

    std::string product = rule[0].getRules()[0];
    CHECK_EQ(product, "bbXa");
}

TEST_CASE("display")
{
    Grammar g1;
    g1.addLetterToTerminals('a');
    g1.addLetterToTerminals('b');
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');
    g1.addStartVariable('S');
    ProductionRule g11('S', std::vector<std::string>{"aSb", "XX", "epsilon"});
    ProductionRule g12('X', std::vector<std::string>{"bbXa", "S"});
    g1.addRule(g11);
    g1.addRule(g12);

    std::ostringstream oss;
    g1.display(oss);

    CHECK(oss.str() == "t a b\nv S X\ns S\nr0 S aSb XX epsilon\nr1 X bbXa S");
}

TEST_CASE("clear")
{
    Grammar g1;
    g1.addLetterToTerminals('a');
    g1.addLetterToTerminals('b');
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');
    g1.addStartVariable('S');
    ProductionRule g11('S', std::vector<std::string>{"aSb", "XX", "epsilon"});
    ProductionRule g12('X', std::vector<std::string>{"bbXa", "S"});
    g1.addRule(g11);
    g1.addRule(g12);

    g1.clear();

    CHECK_EQ(g1.getId(), "");
    CHECK(!g1.getVariable('S'-'A'));
    CHECK(!g1.getVariable('X'-'A'));
    CHECK(!g1.getTerminal('a'-'a'));
    CHECK(!g1.getTerminal('b'-'a'));
    CHECK_EQ(g1.getStartVariable(), '\0');
}

TEST_CASE("chomsky")
{
    Grammar g1;
    g1.addLetterToTerminals('a');
    g1.addLetterToTerminals('b');
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');
    g1.addStartVariable('S');
    ProductionRule g11('S', std::vector<std::string>{"a", "XX"});
    ProductionRule g12('X', std::vector<std::string>{"b", "a"});
    g1.addRule(g11);
    g1.addRule(g12);

    SUBCASE("grammar is in chomsky normal form")
    {
        CHECK(g1.chomsky());
    }
    SUBCASE("grammar is not in chomsky normal form")
    {
        ProductionRule g13('X', std::vector<std::string>{"baaaaaaaaa", "a"});
        g1.addRule(g13);
        CHECK(!g1.chomsky());
    }
}

TEST_CASE("isEmpty")
{
    Grammar g1;
    g1.addLetterToTerminals('a');
    g1.addLetterToTerminals('b');
    g1.addLetterToVariables('S');
    g1.addLetterToVariables('X');
    g1.addStartVariable('S');
    ProductionRule g11('S', std::vector<std::string>{"aSb", "XX", "epsilon"});
    ProductionRule g12('X', std::vector<std::string>{"bbXa", "S"});

    CHECK(g1.isEmpty());
}
