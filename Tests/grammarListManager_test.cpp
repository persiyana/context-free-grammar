#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../libs/doctest.h"
#include "../GrammarListManager/grammarListManager.hpp"
#include "../SharedData/sharedData.hpp"
#include "../Grammar/grammar.hpp"
#include "../ProductionRule/productionRule.hpp"

TEST_CASE("list() makes a list of the ids of all grammars on the list")
{
    GrammarListManager manager;
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
    Grammar g2;
    g2.addLetterToTerminals('0');
    g2.addLetterToTerminals('1');
    g2.addLetterToVariables('R');
    g2.addLetterToVariables('M');
    g2.addStartVariable('M');
    ProductionRule g21('M', std::vector<std::string>{"00M1", "R010", "0"});
    ProductionRule g22('R', std::vector<std::string>{"111M", "epsilon"});
    g2.addRule(g21);
    g2.addRule(g22);

    SharedData::grammarList.push_back(g1);
    SharedData::grammarList.push_back(g2);

    std::string result = manager.list();

    CHECK_EQ(result, "1SX\n2MR");
}

TEST_CASE("addRule(id, newRule) adds a new rule to grammar with id id")
{
    GrammarListManager manager;

    ProductionRule g13('X', std::vector<std::string>{"aS", "b"});
    std::string result = manager.addRule("1SX", g13);

    CHECK_EQ(result, "Successfully added new rule\n");
}

TEST_CASE("removeRule(id, number) removes the rule in prosition number of grammar with id id")
{
    GrammarListManager manager;

    std::string result = manager.removeRule("1SX", 2);

    CHECK_EQ(result, "Succesfully removed rule 2 from grammar 1SX\n");
}

TEST_CASE("unite(id1, id2) returns the id of the new grammar that is created by the union of grammars with ids id1 and id2")
{
    GrammarListManager manager;
    std::string newId = manager.unite(SharedData::grammarList[0].getId(), SharedData::grammarList[1].getId());
    CHECK_EQ(newId, "3AMRSX");
}

TEST_CASE("concat(id1, id2) returns the id of the new grammar that is created by the concatenation of grammars with ids id1 and id2")
{
    GrammarListManager manager;
    std::string newId = manager.concat(SharedData::grammarList[0].getId(), SharedData::grammarList[1].getId());
    CHECK_EQ(newId, "4AMRSX");
}

TEST_CASE("chomsky(id) returns whether grammar with id id is in chomsky normal form")
{
    GrammarListManager manager;
    std::string isChomsky = manager.chomsky(SharedData::grammarList[0].getId());
    CHECK_EQ(isChomsky, "Grammar with id " + SharedData::grammarList[0].getId() + " is not in Chomsky normal form");
}

TEST_CASE("iter(id) returns the id of the new grammar, created by the iteration of grammar with id id")
{
    GrammarListManager manager;
    std::string newId = manager.iter(SharedData::grammarList[0].getId());
    CHECK_EQ(newId, "5ASX");
}

TEST_CASE("empty(id) returns whether the language of grammar with id id is empty")
{
    GrammarListManager manager;
    std::string res = manager.empty(SharedData::grammarList[0].getId());
    CHECK_EQ(res, "The language of grammar with id " + SharedData::grammarList[0].getId() + " is not empty");
}
