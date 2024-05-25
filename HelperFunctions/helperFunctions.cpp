#include "helperFunctions.hpp"

std::vector<std::string> HelperFunctions::split(const std::string& str, char delim )
{
    std::vector<std::string> result;

	std::stringstream ss;
	ss << str;

	std::string temp;
	while (std::getline(ss, temp, delim))
	{
        if(temp != "")
        {
            result.push_back(temp);
        }
	}

	return result;
}

std::string HelperFunctions::uniteVector(const std::vector<std::string>& vect, char delim)
{
    if (vect.empty())
    {
        return "";
    }

    std::ostringstream result;

    for (size_t i = 0; i < vect.size()-1; i++)
    {
        result << vect[i] << delim;
    }

    result << vect[vect.size()-1];

    return result.str();
}

bool HelperFunctions::contains(const std::string& str, char ch)
{
    return std::find(str.begin(), str.end(), ch) != str.end();
}