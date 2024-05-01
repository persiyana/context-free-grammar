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
    void print();////////
    //void exit();
private:
    std::string fileDirectory = "";
    std::string fileName = "";
    std::string getFileNameFromDir();
    std::vector<Grammar> grammarList;
    
    std::vector<std::string> split(std::string);
};