#pragma once

#include <iostream>
#include <vector>

#include "../Grammar/grammar.hpp"
#include "../SharedData/sharedData.hpp"

class GrammarListManager
{
private:
    char unusedVariable(Grammar) const;
    void changeVariables(const std::string& id1, const std::string& id2);
public:
    std::string list() const;
    std::string addRule(const std::string& id, const ProductionRule& rule);
    std::string removeRule(const std::string& id, size_t number);
    std::string unite(const std::string& id1, const std::string& id2);
    std::string concat(const std::string& id1, const std::string& id2);
    std::string chomsky(const std::string& id) const;
    std::string cyk(const std::string& id, const std::string& word);
    std::string iter(const std::string& id);
    std::string empty(const std::string& id) const;
    std::string chomskify(const std::string& id);
};