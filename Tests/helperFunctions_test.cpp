#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../libs/doctest.h"
#include "../HelperFunctions/helperFunctions.hpp"

TEST_CASE("contains() is defined properly")
{
    std::vector<std::string> arr({"one", "two", "three"});
    SUBCASE("returns true if element is in the array")
    {
        CHECK(HelperFunctions::contains<std::vector<std::string>, std::string>(arr, "two"));
    }
    SUBCASE("returns false if element is not in the array")
    {
        CHECK(!HelperFunctions::contains<std::vector<std::string>, std::string>(arr, "four"));
    }
}

TEST_CASE("split() works correctly")
{
    std::string s = "Some sentence.";
    
    std::vector<std::string> case1 = HelperFunctions::split(s, ' ');
    std::string check1 = case1[1];
    CHECK_EQ(check1, "sentence.");

    std::vector<std::string> case2 = HelperFunctions::split(s, '/');
    std::string check2 = case2[0];
    CHECK_EQ(check2, "Some sentence.");
}

TEST_CASE("uniteVector() works correctly")
{
    std::vector<std::string> s({"Some", "sentence."});
    std::string res1 = HelperFunctions::uniteVector(s, ' ');
    CHECK_EQ(res1, "Some sentence.");

    std::string res2 = HelperFunctions::uniteVector(s, '/');
    CHECK_EQ(res2, "Some/sentence.");
}