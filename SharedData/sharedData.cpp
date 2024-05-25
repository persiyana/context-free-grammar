#include "sharedData.hpp"

std::vector<Grammar> SharedData::grammarList;

int SharedData::indexOfId(const std::string &id)
{
    for (size_t i = 0; i < grammarList.size(); i++)
    {
        if (grammarList[i].getId()==id)
        {
            return i;
        }
        
    }
    throw std::invalid_argument("Id " + id + " not found\n");
}