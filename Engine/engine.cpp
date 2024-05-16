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
            chomsky(args[0]);
        }
        else if(input == "chomskify" && fileIsOpened)
        {
            std::cout << chomskify(args[0]);
        }
        else if(input == "cyk" && fileIsOpened)
        {
            cyk(args[0]);
        }
        else if(input == "iter" && fileIsOpened)
        {
            std::cout << iter(args[0]) << std::endl;
        }
        else if(input == "empty" && fileIsOpened)
        {
            empty(args[0]);
        }
        //the arguments are two id's:
        else if(input == "union" && fileIsOpened)
        {
            std::cout << unite(args[0], args[1]) << std::endl;
        }
        else if(input == "concat" && fileIsOpened)
        {
            std::cout << concat(args[0], args[1])<< std::endl;
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

char Engine::unusedVariable(Grammar grammar) const
{
    char unused = ' ';

    unused = grammar.getUnusedVariable();
    
    return unused;
}

std::string Engine::unite(const std::string& id1, const std::string& id2) //U
{
    int index1 = indexOfId(id1);
    int index2 = indexOfId(id2);
    
    if(index1 == -1 || index1 == -1) 
    {
        return "One or both of id's were not found\n";
    }
    else
    {
        changeVariables(id1, id2);
        std::string newId;
        Grammar united;

        for (size_t i = 0; i < 36; i++)
        {
            if(grammarList[index1].getAlphabet(i) || grammarList[index2].getAlphabet(i))
            {
                united.addLetterToAlphabet(i);
            }
        }
        for (size_t i = 0; i < 26; i++)
        {
            if(grammarList[index1].getVariable(i) || grammarList[index2].getVariable(i))
            {
                united.addLetterToVariables(i);
            }
        }

        char unusedVar = unusedVariable(united);
        if(unusedVar != ' ')
        {
            united.addLetterToVariables(unusedVar);
            united.addStartVariable(unusedVar);

            std::vector<std::string> rules;
            std::string start1 = "", start2 = "";
            start1 += grammarList[index1].getStartVariable();
            start2 += grammarList[index2].getStartVariable();
            rules.push_back(start1);
            rules.push_back(start2);

            Rule newRule(unusedVar, rules);
            united.addRule(newRule);
            newId = united.getId();
        }
        
        std::vector<Rule> rulesIndex1 = grammarList[index1].getRules();
        std::vector<Rule> rulesIndex2 = grammarList[index2].getRules();

        for (size_t i = 0; i < rulesIndex1.size(); i++)
        {
            united.addRule(rulesIndex1[i]);
        }

        for (size_t i = 0; i < rulesIndex2.size(); i++)
        {
            united.addRule(rulesIndex2[i]);
        }

        
        
        grammarList.push_back(united);
        return newId;
    }
}

std::string Engine::concat(const std::string& id1, const std::string& id2) //.
{
    int index1 = indexOfId(id1);
    int index2 = indexOfId(id2);
    
    if(index1 == -1 || index1 == -1) 
    {
        return "One or both of id's were not found\n";
    }
    else
    {
        changeVariables(id1, id2);
        std::string newId;
        Grammar concatenated;

        for (size_t i = 0; i < 36; i++)
        {
            if(grammarList[index1].getAlphabet(i) || grammarList[index2].getAlphabet(i))
            {
                concatenated.addLetterToAlphabet(i);
            }
        }
        for (size_t i = 0; i < 26; i++)
        {
            if(grammarList[index1].getVariable(i) || grammarList[index2].getVariable(i))
            {
                concatenated.addLetterToVariables(i);
            }
        }
        char unusedVar = unusedVariable(concatenated);
        if(unusedVar != ' ')
        {
            concatenated.addLetterToVariables(unusedVar);
            concatenated.addStartVariable(unusedVar);

            std::vector<std::string> rules;
            std::string start = "";
            start += grammarList[index1].getStartVariable();
            start += grammarList[index2].getStartVariable();
            rules.push_back(start);
            rules.push_back("epsilon");
            Rule newRule(unusedVar, rules);
            concatenated.addRule(newRule);
            newId = concatenated.getId();
        }
        
        std::vector<Rule> rulesIndex1 = grammarList[index1].getRules();
        std::vector<Rule> rulesIndex2 = grammarList[index2].getRules();

        for (size_t i = 0; i < rulesIndex1.size(); i++)
        {
            concatenated.addRule(rulesIndex1[i]);
        }

        for (size_t i = 0; i < rulesIndex2.size(); i++)
        {
            concatenated.addRule(rulesIndex2[i]);
        }

        
        
        grammarList.push_back(concatenated);
        return newId;
    }
}

std::string Engine::iter(const std::string& id) //*
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found";
    }
    else
    {
        char unused = unusedVariable(grammarList[index]);
        std::string newId = "";
        if(unused != ' ')
        {
            Grammar iter = grammarList[index];
            
            iter.addLetterToVariables(unused);
            std::vector<std::string> varRules;
            varRules.push_back("epsilon");
            std::string rule;
            rule.push_back(grammarList[index].getStartVariable());
            rule.push_back(unused);
            varRules.push_back(rule);
            iter.addStartVariable(unused);
            Rule newRule(unused, varRules);
            iter.addRule(newRule);

            grammarList.push_back(iter);
            newId = iter.getId();
        }
        return newId;
    }
}

void Engine::changeVariables(const std::string& id1, const std::string& id2)
{
    
    int index1 = indexOfId(id1);
    int index2 = indexOfId(id2);
    
    if(index1 == -1 || index1 == -1) 
    {
        std::cout << "One or both of id's were not found\n";
    }
    else
    {
        std::vector<size_t> indexesOfUnusedVariables;

        for (size_t i = 0; i < 26; i++)
        {
            if(grammarList[index1].getVariable(i) == false && grammarList[index2].getVariable(i) == false)
            {
                indexesOfUnusedVariables.push_back(i);
            }
        }

        for (size_t i = 0; i < 26; i++)
        {
            if(grammarList[index1].getVariable(i) == true && grammarList[index2].getVariable(i) == true)
            {
                size_t indexOfUnusedLetter = indexesOfUnusedVariables[indexesOfUnusedVariables.size() - 1];
                grammarList[index2].changeVariable(i, indexOfUnusedLetter);
                indexesOfUnusedVariables.pop_back();
                size_t startVar2 = grammarList[index2].getStartVariable() - 'A';
                if(startVar2 == i)
                {
                    char variable = indexOfUnusedLetter + 'A';
                    grammarList[index2].addStartVariable(variable);
                }
            }
        }

    }
}



void Engine::cyk(const std::string& id) const
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        std::cout << "Id not found\n";
    }
    else
    {

    }
}

void Engine::empty(const std::string& id) const
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        std::cout << "Id not found\n";
    }
    else
    {

    }
}

std::string Engine::chomskify(const std::string& id)
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found\n";
    }
    else
    {

    }
}

void Engine::chomsky(const std::string& id) const
{
    int index = indexOfId(id);
    
    if(index == -1) 
    {
        std::cout << "Id not found\n";
    }
    else
    {

    }
}