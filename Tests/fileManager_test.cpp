#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../libs/doctest.h"
#include "../SharedData/sharedData.hpp"
#include "../FileManager/fileManager.hpp"

TEST_CASE("open(fileDirectory)")
{
    FileManager fileManager;

    SUBCASE("Test opening existing file") {
        std::string fileDir = "TestFiles/test.txt";
        CHECK_NOTHROW(fileManager.open(fileDir));
        CHECK_EQ(SharedData::grammarList.size(), 2);
    }
    SUBCASE("Test opening not existing file")
    {
        std::string fileDir = "TestFiles/not.txt";
        CHECK_THROWS_AS(fileManager.open(fileDir), std::runtime_error);
    }

    fileManager.close();
}

TEST_CASE("close()")
{
    FileManager fileManager;
    std::string fileDir = "TestFiles/test.txt";
    fileManager.open(fileDir);
    std::string res = fileManager.close();
    CHECK_EQ(SharedData::grammarList.size(), 0);
    CHECK_EQ(res, "Succesfully closed test.txt\n");
    fileManager.close();
}

TEST_CASE("saveAs")
{
    FileManager fileManager;
    std::string fileDir = "TestFiles/test.txt";
    fileManager.open(fileDir);
    
    std::string result = fileManager.saveAs("sth.txt");
    CHECK_EQ(result, "Successfully saved another sth.txt\n");
    fileManager.close();
}

TEST_CASE("save")
{
     FileManager fileManager;
    std::string fileDir = "TestFiles/test.txt";
    fileManager.open(fileDir);
    
    std::string result = fileManager.save();
    CHECK_EQ(result, "Successfully saved\n");
    fileManager.close();
}

TEST_CASE("saveGrammar")
{
    FileManager fileManager;
    std::string fileDir = "TestFiles/test.txt";
    fileManager.open(fileDir);
    
    std::string result = fileManager.saveGrammar(SharedData::grammarList[0].getId(), "gr.txt");
    CHECK_EQ(result, "Successfully saved gr.txt\n");
    fileManager.close();
}

TEST_CASE("printGrammar")
{
    FileManager fileManager;
    std::string fileDir = "TestFiles/test.txt";
    fileManager.open(fileDir);

    CHECK_NOTHROW(fileManager.printGrammar(SharedData::grammarList[0].getId()));

    fileManager.close();
}