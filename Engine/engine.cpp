#include "engine.hpp"

Engine& Engine::getInstance()
{
    static Engine instance;
    return instance;
}

void Engine::run()
{
    std::string command, arguments, response = "";
    bool fileIsOpened = false;
    std::cout << "> ";
    std::cin >> command;
    std::getline(std::cin, arguments);

    while(command != "exit")
    {   
        try
        {
            std::vector<std::string> args = HelperFunctions::split(arguments, ' '); 
            //without arguments:
            if(command == "help") 
            {   
                help();
            }
            //the argument is a file directory:
            else if(command == "open")
            {
                response = fileManager.open(HelperFunctions::uniteVector(args, ' '));
                fileIsOpened = true;
            }
            else if(fileIsOpened)
            {
                //without arguments:
                if(command == "close")
                {
                    response = fileManager.close();
                    fileIsOpened = false;
                }
                else if(command == "list")
                {
                    response = grammarListManager.list();
                } 
                //has either no arguments or arguments for id and filename
                else if(command == "save")
                {
                    if(args.size() == 0)
                    {
                        response = fileManager.save();
                    }
                    else
                    {
                        std::string id = args[0];
                        args.erase(args.begin());
                        response = fileManager.saveGrammar(id, HelperFunctions::uniteVector(args, ' '));
                    }
                }
                //the argument is a file directory:
                else if(command == "saveas")
                {
                    response = fileManager.saveAs(HelperFunctions::uniteVector(args, ' '));
                }
                //the argument is one id:
                else if(command == "print")
                {
                    response = fileManager.printGrammar(args[0]);
                }
                else if(command == "chomsky")
                {
                    response = grammarListManager.chomsky(args[0]);
                }
                else if(command == "chomskify")
                {
                    response = grammarListManager.chomskify(args[0]);
                }
                else if(command == "iter")
                {
                    response = grammarListManager.iter(args[0]);
                }
                else if(command == "empty")
                {
                    response = grammarListManager.empty(args[0]);
                }
                //the arguments are id and a word
                else if(command == "cyk")
                {
                    response = grammarListManager.cyk(args[0], args[1]);
                }
                //the arguments are two id's:
                else if(command == "union")
                {
                    response = grammarListManager.unite(args[0], args[1]);
                }
                else if(command == "concat")
                {
                    response = grammarListManager.concat(args[0], args[1]);
                }
                //the arguments are id and new rule:
                else if(command == "addRule")
                {
                    std::string id = args[0];
                    std::string variable = args[1];
                    args.erase(args.begin()); //removes id from args
                    args.erase(args.begin()); //removes variable from args

                    if(variable.size() > 1) {
                        throw std::out_of_range("The variables of the rules must contain only one char so this rule will not be added."); 
                    }

                    ProductionRule newRule(variable[0], args);

                    response = grammarListManager.addRule(id, newRule);
                }
                //the arguments are id and a number of a rule:
                else if(command == "removeRule")
                {
                    //converts args[1] to a size_t object
                    std::stringstream stream(args[1]);  
                    size_t ruleIndex;
                    stream >> ruleIndex;

                    response = grammarListManager.removeRule(args[0], ruleIndex);
                }
                else
                {
                    response = command + " is invalid command";
                }
            }
            else
            {
                response = "Please open a file before entering another command";
            }
            
            
            std::cout << response << std::endl;
            std::cout << "> ";
            std::cin >> command;
            std::getline(std::cin, arguments);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << "Exiting the program...\n";
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



