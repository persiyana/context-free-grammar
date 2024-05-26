#include "fileManager.hpp"

std::string FileManager::getFileNameFromDir(const std::string& fileDirectoryName) const
{
    size_t pos = fileDirectoryName.find_last_of("/\\");

    if (pos == std::string::npos)
    {
        return fileDirectoryName;
    }

    return fileDirectoryName.substr(pos + 1);

}

std::string FileManager::open(const std::string& fileDir)
{	
    fileDirectory = fileDir;

    fileName = getFileNameFromDir(fileDirectory);

    std::ifstream file(fileDirectory);

    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file: " + fileName);
    }
    
    std::string line;
    Grammar currentGrammar;

    while(std::getline(file, line)){
        try
        {
            std::vector<std::string> lineVector = HelperFunctions::split(line);
            if(lineVector[0] == ";")
            {
                SharedData::grammarList.push_back(currentGrammar);
                currentGrammar.clear();
            }
            else if(lineVector[0] == "t")
            {
                for (size_t i = 1; i < lineVector.size(); i++)
                {
                    if(lineVector[i].length() == 1){
                        currentGrammar.addLetterToTerminals(lineVector[i][0]);
                    }
                    else
                    {
                        throw std::invalid_argument("`" + lineVector[i] + "` is an invalid terminal and won't be added to the grammar");
                    }
                    
                }
            }
            else if(lineVector[0] == "v")
            {
                for (size_t i = 1; i < lineVector.size(); i++)
                {
                    if(lineVector[i].length() == 1){
                        currentGrammar.addLetterToVariables(lineVector[i][0]);
                    }
                     else
                    {
                        throw std::invalid_argument("`" + lineVector[i] + "` is an invalid variable and won't be added to the grammar");
                    }
                }
            }
            else if(lineVector[0] == "s")
            {
                if(lineVector[1].length() == 1){
                    currentGrammar.addStartVariable(lineVector[1][0]);
                }
                else
                {
                    throw std::invalid_argument("`" + lineVector[1] + "` is an invalid variable and won't be added to the grammar");
                }
            }

            else if(lineVector[0][0] == 'r')
            {
                ProductionRule currentRule;
                if(lineVector[1].length() == 1){
                    currentRule.setVariable(lineVector[1][0]);
                }
                if(currentRule.getVariable() != '\0')
                {
                    for (size_t i = 2; i < lineVector.size(); i++)
                    {
                        currentRule.addRule(lineVector[i]);
                    }
                    
                }
                else
                {
                    std::string currentRuleAsString = "";
                    for (size_t i = 0; i < lineVector.size(); i++)
                    {
                        currentRuleAsString += lineVector[i]+ " ";
                    }
                    
                    throw std::invalid_argument("The rule `" + currentRuleAsString + "` will not be added to the grammar");
                }
                currentGrammar.addRule(currentRule);
            }
            else
            {
                throw std::invalid_argument("`" + lineVector[0] + "` is invalid line start");
            }
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }
    
    file.close();

    return "Successfully opened " + fileName;
}

std::string FileManager::close()
{
    fileDirectory = "";
    SharedData::grammarList.clear();
    std::string result = "Succesfully closed " + fileName + '\n';
    fileName = "";
    Grammar::grammarsCount = 0;
    return result;
}

void FileManager::display(std::ostream& file) const
{
    for (size_t i = 0; i < SharedData::grammarList.size(); i++)
    {
        SharedData::grammarList[i].display(file);
        file << std::endl << ";" << std::endl;
    }
}

std::string FileManager::saveAs(const std::string& fileDir) const
{
    std::ofstream file(fileDir);
    if (!file.is_open())
	{
		throw std::runtime_error("File is not open\n");
	}
    display(file);
    file.close();
    return "Successfully saved another " + getFileNameFromDir(fileDir) +"\n";
}

std::string FileManager::save() const
{
    saveAs(fileDirectory);
    return "Successfully saved\n";
}

std::string FileManager::saveGrammar(const std::string& id, const std::string& fileDir) const
{
    int index = SharedData::indexOfId(id);
    
    std::ofstream file(fileDir);
    if (!file.is_open())
    {
        throw std::runtime_error("File is not open\n");
    }
    SharedData::grammarList[index].display(file);
    file << std::endl << ';';
    file.close();
    return "Successfully saved " + getFileNameFromDir(fileDir) + '\n';

}

std::string FileManager::printGrammar(const std::string& id) const
{
    int index = SharedData::indexOfId(id);
    
    SharedData::grammarList[index].display();
    return "";
}