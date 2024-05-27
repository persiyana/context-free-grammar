#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../libs/doctest.h"
#include "../ProductionRule/productionRule.hpp"

TEST_CASE("ProductionRule constructors are working properly")
{
    SUBCASE("Default constructor")
    {
        ProductionRule case0;
        CHECK_EQ(case0.getVariable(), '\0');
    }
    SUBCASE("Arguments are char and char")
    {
        ProductionRule case1('A', 'a');
        CHECK_EQ(case1.getVariable(), 'A');
        CHECK_EQ(case1.getRules()[0][0], 'a');
    }
    SUBCASE("Arguments are char and std::string")
    {
        ProductionRule case2('B', "epsilon");
        CHECK_EQ(case2.getVariable(), 'B');
        CHECK_EQ(case2.getRules()[0], "epsilon");
    }
    SUBCASE("Arguments are char and std::vector<std::string>")
    {
        ProductionRule case3('C', std::vector<std::string>{"c", "epsilon"});
        CHECK_EQ(case3.getVariable(), 'C');
        CHECK_EQ(case3.getRules()[1], "epsilon");
    }
}

TEST_CASE("setVariable(letter) is setting the variable correctly")
{
    SUBCASE("test with valid input")
    {
        ProductionRule case1;
        case1.setVariable('A');
        CHECK_EQ(case1.getVariable(), 'A');
    }
    SUBCASE("test with invalid input")
    {
        ProductionRule case2;
        CHECK_THROWS_AS(case2.setVariable('b'), std::invalid_argument);
    }
}

TEST_CASE("changeVariable(oldVariable, newVariable) changes the variable correctly")
{
    ProductionRule case1('A', std::vector<std::string>{"cA", "A" ,"epsilon"});
    SUBCASE("with letter that is in the rule")
    {
        case1.changeVariable('A', 'R');
        CHECK_EQ(case1.getVariable(), 'R');
        CHECK_EQ(case1.getRules()[0], "cR");
        CHECK_EQ(case1.getRules()[1], "R");
        CHECK_EQ(case1.getRules()[2], "epsilon");
    }
    SUBCASE("with letter that is not in the rule")
    {
        case1.changeVariable('e', 'R');
        CHECK_EQ(case1.getVariable(), 'A');
        CHECK_EQ(case1.getRules()[0], "cA");
        CHECK_EQ(case1.getRules()[1], "A");
        CHECK_EQ(case1.getRules()[2], "epsilon");
    }
}

TEST_CASE("removeVariable(letter) removes all instances of the variable in the rules")
{
    ProductionRule case1('A', std::vector<std::string>{"cA", "A" ,"epsilon"});
    case1.removeVariable('A');
    CHECK_EQ(case1.getVariable(), 'A');
    
    CHECK_EQ(case1.getRules()[0], "c");
    CHECK_EQ(case1.getRules()[1], "epsilon");
}

TEST_CASE("chomsky() works properly")
{
    SUBCASE("Rule is in chomsky normal form")
    {
        ProductionRule prod1('S', std::vector<std::string>{"a", "XY"});
        CHECK(prod1.chomsky());
        ProductionRule prod2('S', std::vector<std::string>{"a", "epsilon", "XY"});
        CHECK(prod2.chomsky());
    }
    SUBCASE("Rule is not in chomsky normal form")
    {
        ProductionRule prod3('S', std::vector<std::string>{"ab", "XY"});
        CHECK(!prod3.chomsky());
        ProductionRule prod4('S', std::vector<std::string>{"a", "X"});
        CHECK(!prod4.chomsky());
    }
}

TEST_CASE("display function works properly")
{
    ProductionRule pr;
    pr.setRules({"rule1", "rule2", "rule3"}) ;

    std::ostringstream oss;
    pr.display(oss);

    CHECK(oss.str() == " rule1 rule2 rule3");
}

TEST_CASE("hasLetterAsProduct(letter)")
{
    SUBCASE("have the letter in products")
    {
        ProductionRule prod1('S', std::vector<std::string>{"a", "A" ,"XY"});
        CHECK(prod1.hasLetterAsProduct('A'));
    }
    SUBCASE("does not have the letter in products")
    {
        ProductionRule prod2('S', std::vector<std::string>{"a","XY"});
        CHECK(!prod2.hasLetterAsProduct('A'));
    }
}

TEST_CASE("isNullable(nullableVariables)")
{
    std::vector<char> nullableVariables({'A', 'B'});

    SUBCASE("rule is nullable")
    {
        ProductionRule prod1('S', std::vector<std::string>{"a","XY", "AB"});
        CHECK(prod1.isNullable(nullableVariables));
        ProductionRule prod2('S', std::vector<std::string>{"a","XY","epsilon"});
        CHECK(prod2.isNullable(nullableVariables));
    }
    SUBCASE("rule is not nullable")
    {
        ProductionRule prod3('S', std::vector<std::string>{"a", "XY"});
        CHECK(!prod3.isNullable(nullableVariables));
    }
}

TEST_CASE("replaceNullable(nullableVariables)")
{
    std::vector<char> nullableVariables({'B', 'C'});
    ProductionRule prod('S', std::vector<std::string>{"ABCd","a","epsilon", "Ab"});
    prod.replaceNullable(nullableVariables);
    CHECK_EQ(prod.getRules()[0], "ABCd");
    CHECK_EQ(prod.getRules()[1], "a");
    CHECK_EQ(prod.getRules()[2], "Ab");
    CHECK_EQ(prod.getRules()[3], "ACd");
    CHECK_EQ(prod.getRules()[4], "ABd");
    CHECK_EQ(prod.getRules()[5], "Ad");
}