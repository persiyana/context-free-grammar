#include "engine.hpp"

void Engine::run()
{
    std::string input, arguments;
    bool fileIsOpened = false;
    std::cin >> input;
    
    std::getline(std::cin, arguments);
    

    while(input != "exit")
    {   
        
        std::vector<std::string> args = HelperFunctions::split(arguments, ' '); 
        //without arguments:
        if(input == "help") 
        {   
            help();
        }
        else if(input == "close" && fileIsOpened)
        {
            std::cout << close();
            fileIsOpened = false;
        }
        else if(input == "list" && fileIsOpened)
        {
            list();
        } 
        //has either no arguments or arguments for id and filename
        else if(input == "save" && fileIsOpened)
        {
            if(args.size() == 0)
            {
                std::cout << save();
            }
            else
            {
                std::string id = args[0];
                args.erase(args.begin());
                std::cout << saveGrammar(id, HelperFunctions::uniteVector(args, ' '));
            }
        }
        //the argument is a file directory:
        else if(input == "open")
        {
            std::cout << open(HelperFunctions::uniteVector(args, ' '));
            fileIsOpened = true;
        }
        else if(input == "saveas" && fileIsOpened)
        {
            std::cout << saveAs(HelperFunctions::uniteVector(args, ' '));
        }
        //the argument is one id:
        else if(input == "print" && fileIsOpened)
        {
            print(args[0]);
        }
        else if(input == "chomsky" && fileIsOpened)
        {
            std::cout << chomsky(args[0]);
        }
        else if(input == "chomskify" && fileIsOpened)
        {
            chomskify(args[0]);
        }
        else if(input == "cyk" && fileIsOpened)
        {
            cyk(args[0]);
        }
        else if(input == "iter" && fileIsOpened)
        {
            iter(args[0]);
        }
        else if(input == "empty" && fileIsOpened)
        {
            empty(args[0]);
        }
        //the arguments are two id's:
        else if(input == "union" && fileIsOpened)
        {
            unite(args[0], args[1]);
        }
        else if(input == "concat" && fileIsOpened)
        {
            concat(args[0], args[1]);
        }
        //the arguments are id and new rule:
        else if(input == "addRule" && fileIsOpened)
        {
            std::string id = args[0];
            std::string variable = args[1];
            args.erase(args.begin());
            args.erase(args.begin());

            if(variable.size() > 1) {
                std::cout << "The variable for this rule would be only `" << variable[0] << "`" << std::endl;
            }
            Rule newRule(variable[0], args);

            std::cout << addRule(id, newRule);
        }
        //the arguments are id and a number of a rule:
        else if(input == "removeRule" && fileIsOpened)
        {
            size_t number = std::stoul(args[1]);
            std::cout << removeRule(args[0], number);
        }
        else
        {
            std::cout << input <<" is invalid command" << std::endl;
        }
        std::cin >> input;
        std::getline(std::cin, arguments);
    }
    
    std::cout << "Exiting the program...";
}

void Engine::help() const
{
    std::cout << "The following commands are supported:" <<
    std::endl << "open <file>           opens <file>" <<
    std::endl << "close                 closes currently opened file" << 
    std::endl << "save                  saves the currently open file" << 
    std::endl << "saveas <file>         saves the currently open file in <file>" << 
    std::endl << "help                  prints this information" << 
    std::endl << "exit                  exists the program" << 
    std::endl << "list                  list of the IDs of all grammars read" << 
    std::endl << "print <id>            prints grammar with id <id>" << 
    std::endl << "save <id> <filename>  saves grammar with id <id> in file <filename>" << 
    std::endl << "addRule <id> <rule>   adds rule <rule> to grammar with id <id>" << 
    std::endl << "removeRule <id> <n>   removes rule with number <n> from grammar with id <id>" << 
    std::endl << "union <id1> <id2>     unites grammar with id <id1> and grammar with id <id2> and prints the id of the new grammar" << 
    std::endl << "concat <id1> <id2>    concatenates grammar with id <id1> and grammar with id <id2> and prints the id of the new grammar" << 
    std::endl << "chomsky <id>          checks whether grammar with id <id> is in Chomsky normal form" << 
    std::endl << "cyk <id> <word>       checks if a word <word> is in the language of grammar with id <id>" << 
    std::endl << "iter <id>             finds the result of operation 'iteration' over grammar with id <id> and prints the id of the new grammar" << 
    std::endl << "empty <id>            checks if the language of grammar with id <id> is empty" << 
    std::endl << "chomskify <id>        converts grammar with id <id> and prints the id of the new grammar" << std::endl;
}

std::string Engine::open(const std::string& fileDir)
{	
    fileDirectory = fileDir;

    fileName = HelperFunctions::getFileNameFromDir(fileDirectory);

    std::ifstream file(fileDirectory);

    if (!file.is_open())
    {
        return "Error opening file: " + fileName + '\n';
    }

    
    
    std::string line;
    Grammar currentGrammar;

    while(std::getline(file, line)){
        
        std::vector<std::string> lineVector = HelperFunctions::split(line);
        if(lineVector[0] == ";")
        {
            currentGrammar.setId(grammarList.size());
            grammarList.push_back(currentGrammar);
            currentGrammar.clear();
        }
        else if(lineVector[0] == "a")
        {
            for (size_t i = 1; i < lineVector.size(); i++)
            {
                if(lineVector[i].length() == 1){
                    currentGrammar.addLetterToAlphabet(lineVector[i][0]);
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
            Rule currentRule;
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

    return "Successfully opened " + fileName +'\n';
}

std::string Engine::close()
{
    fileDirectory = "";
    grammarList.clear();
    std::string result = "Succesfully closed " + fileName + '\n';
    fileName = "";
    return result;
}

std::string Engine::save() const
{
    saveAs(fileDirectory);
    return "Successfully saved\n";
}

std::string Engine::saveGrammar(const std::string& id, const std::string& fileDir) const
{
    int index = indexOfId(id);
    
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
        grammarList[index].display(file);
        file << std::endl << ';';
        file.close();
        return "Successfully saved " +  HelperFunctions::getFileNameFromDir(fileDir) + '\n';
    }
}

std::string Engine::saveAs(const std::string& fileDir) const
{
    std::ofstream file(fileDir);
    if (!file.is_open())
	{
		return "File is not open\n";
	}
    display(file);
    file.close();
    return "Successfully saved another " + HelperFunctions::getFileNameFromDir(fileDir) +"\n";
}

void Engine::display(std::ostream& file) const
{

    for (size_t i = 0; i < grammarList.size(); i++)
    {
        grammarList[i].display(file);
        file << std::endl << ";" << std::endl;
    }
   
}

void Engine::list() const
{
    for (size_t i = 0; i < grammarList.size(); i++)
    {
        std::cout << grammarList[i].getId() << std::endl;
    }
    
}

void Engine::print(const std::string& id) const
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        std::cout << "Id not found" << std::endl;
    }
    else
    {
        grammarList[index].display();
        std::cout << std::endl;
    }
}

std::string Engine::removeRule(const std::string& id, size_t number)
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found\n";
    }
    else
    {
        grammarList[index].removeRule(number);
        return "Succesfully removed rule " + std::to_string(number) + " from grammar " + id + '\n';
    }
    
}

std::string Engine::addRule(const std::string& id, const Rule& rule)
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found\n";
    }
    else
    {
        grammarList[index].addRule(rule);
        return "Successfully added new rule\n";
    }
}

std::string Engine::chomsky(const std::string& id) const
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found\n";
    }
    else
    {
        if(grammarList[index].containsE())
        {
            return "This grammar is not in Chomsky normal form\n";
        }
        else
        {
            return "This grammar is in Chomsky normal form\n";
        }
    }
}

int Engine::indexOfId(const std::string& id) const
{
    size_t i = 0;
    while ( i < grammarList.size() && grammarList[i].getId()!=id)
    {
        i++;
    }
    
    if(i == grammarList.size() && grammarList[i].getId()!=id) 
    {
       return -1;
    }
    return i;
}

void Engine::unite(const std::string& id1, const std::string& id2)
{

}
void Engine::concat(const std::string& id1, const std::string& id2)
{

}
void Engine::cyk(const std::string& id) const
{

}
void Engine::iter(const std::string& id)
{

}
void Engine::empty(const std::string& id) const
{

}
void Engine::chomskify(const std::string& id)
{

}