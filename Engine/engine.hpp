#include <iostream>
#include <vector>

#include "../Grammar/grammar.hpp"

class Engine
{
public:
    Engine() = default;
    Engine(std::string);
    void open();
    void close();
    void save();
    void saveAs();
    void help();
    void print(std::ofstream&);////////
    void list();
    void print();
    void saveGrammar(std::string);
    void removeRule();
    void addRule();
    //void exit();
private:
    std::string fileDirectory = "";
    std::string fileName = "";
    std::string getFileNameFromDir(std::string);
    std::vector<Grammar> grammarList;
    
    std::vector<std::string> split(std::string);
};