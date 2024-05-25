#include "fileManager.hpp"

std::string FileManager::getFileNameFromDir(const std::string& fileDirectoryName) const
{
    std::string temp = "";

    int i = fileDirectoryName.length()-1;

    while(i >= 0 && fileDirectoryName[i] != '\\')
    {
        temp.push_back(fileDirectoryName[i--]);
    }
    std::reverse(temp.begin(), temp.end());

    return temp;
}

std::string FileManager::open(const std::string& fileDir)
{	
    fileDirectory = fileDir;

    fileName = getFileNameFromDir(fileDirectory);

    std::ifstream file(fileDirectory);

    if (!file.is_open())
    {
        return "Error opening file: " + fileName;
    }
    
    std::string line;
    Grammar currentGrammar;

    while(std::getline(file, line)){
        
        std::vector<std::string> lineVector = HelperFunctions::split(line);
        if(lineVector[0] == ";")
        {
            SharedData::grammarList.push_back(currentGrammar);
            currentGrammar.clear();
        }
        else if(lineVector[0] == "a")
        {
            for (size_t i = 1; i < lineVector.size(); i++)
            {
                if(lineVector[i].length() == 1){
                    currentGrammar.addLetterToTerminals(lineVector[i][0]);
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
                
            }
        }
        else if(lineVector[0] == "s")
        {
            if(lineVector[1].length() == 1){
                currentGrammar.addStartVariable(lineVector[1][0]);
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
            currentGrammar.addRule(currentRule);
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
		return "File is not open\n";
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
    
    if(index == -1) 
    {
        return "Id not found" + '\n';
    }
    else{
        std::ofstream file(fileDir);
        if (!file.is_open())
        {
            return "File is not open\n";
        }
        SharedData::grammarList[index].display(file);
        file << std::endl << ';';
        file.close();
        return "Successfully saved " + getFileNameFromDir(fileDir) + '\n';
    }
}

std::string FileManager::printGrammar(const std::string& id) const
{
    int index = SharedData::indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found";
    }
    else
    {
        SharedData::grammarList[index].display();
        return "";
    }
}