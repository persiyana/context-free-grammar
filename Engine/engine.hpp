#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "../Grammar/grammar.hpp"
#include "../HelperFunctions/helperFunctions.hpp"
#include "../Rule/rule.hpp"

class Engine
{
public:
    void run();

private:
    std::string fileDirectory = "";
    std::string fileName = "";
    std::vector<Grammar> grammarList;

    std::string open(const std::string& fileDirectory);
    std::string close();
    std::string save() const;
    std::string saveAs(const std::string& fileDirectory) const;
    void help() const;

    void display(std::ostream&) const;

    void list() const;
    void print(const std::string& id) const;
    std::string saveGrammar(const std::string& id, const std::string& fileDirectory) const;
    std::string addRule(const std::string& id, const Rule& rule);
    std::string removeRule(const std::string& id, size_t number);
    void unite(const std::string& id1, const std::string& id2);
    void concat(const std::string& id1, const std::string& id2);
    std::string chomsky(const std::string& id) const;
    void cyk(const std::string& id) const;
    void iter(const std::string& id);
    void empty(const std::string& id) const;
    void chomskify(const std::string& id);

    int indexOfId(const std::string& id) const;
};