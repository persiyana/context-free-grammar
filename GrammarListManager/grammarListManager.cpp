#include "grammarListManager.hpp"

std::string GrammarListManager::list() const
{
    std::string result = "";

    for (size_t i = 0; i < SharedData::grammarList.size()-1; i++)
    {
        result += SharedData::grammarList[i].getId() + "\n";
    }
    result += SharedData::grammarList[SharedData::grammarList.size()-1].getId();

    return result;
}

std::string GrammarListManager::addRule(const std::string& id, const ProductionRule& rule)
{
    int index = SharedData::indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found\n";
    }
    else
    {
        SharedData::grammarList[index].addRule(rule);
        return "Successfully added new rule\n";
    }
}

std::string GrammarListManager::removeRule(const std::string& id, size_t number)
{
    int index = SharedData::indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found\n";
    }
    else
    {
        SharedData::grammarList[index].removeRule(number);
        return "Succesfully removed rule " + std::to_string(number) + " from grammar " + id + '\n';
    }
    
}

char GrammarListManager::unusedVariable(Grammar grammar) const
{
    char unused = ' ';

    unused = grammar.getUnusedVariable();
    
    return unused;
}

void GrammarListManager::changeVariables(const std::string& id1, const std::string& id2)
{
    
    int index1 = SharedData::indexOfId(id1);
    int index2 = SharedData::indexOfId(id2);
    
    if(index1 == -1 || index1 == -1) 
    {
        std::cout << "One or both of id's were not found\n";
    }
    else
    {
        std::vector<size_t> indexesOfUnusedVariables;

        for (size_t i = 0; i < 26; i++)
        {
            if(SharedData::grammarList[index1].getVariable(i) == false && SharedData::grammarList[index2].getVariable(i) == false)
            {
                indexesOfUnusedVariables.push_back(i);
            }
        }

        for (size_t i = 0; i < 26; i++)
        {
            if(SharedData::grammarList[index1].getVariable(i) == true && SharedData::grammarList[index2].getVariable(i) == true)
            {
                size_t indexOfUnusedLetter = indexesOfUnusedVariables[indexesOfUnusedVariables.size() - 1];
                SharedData::grammarList[index2].changeVariable(i, indexOfUnusedLetter);
                indexesOfUnusedVariables.pop_back();
                size_t startVar2 = SharedData::grammarList[index2].getStartVariable() - 'A';
                if(startVar2 == i)
                {
                    char variable = indexOfUnusedLetter + 'A';
                    SharedData::grammarList[index2].addStartVariable(variable);
                }
            }
        }

    }
}

std::string GrammarListManager::unite(const std::string& id1, const std::string& id2) //U
{
    int index1 = SharedData::indexOfId(id1);
    int index2 = SharedData::indexOfId(id2);
    
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
            if(SharedData::grammarList[index1].getTerminals(i) || SharedData::grammarList[index2].getTerminals(i))
            {
                united.addLetterToTerminals(i);
            }
        }
        for (size_t i = 0; i < 26; i++)
        {
            if(SharedData::grammarList[index1].getVariable(i) || SharedData::grammarList[index2].getVariable(i))
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
            start1 += SharedData::grammarList[index1].getStartVariable();
            start2 += SharedData::grammarList[index2].getStartVariable();
            rules.push_back(start1);
            rules.push_back(start2);

            ProductionRule newRule(unusedVar, rules);
            united.addRule(newRule);
            newId = united.getId();
        }
        
        std::vector<ProductionRule> rulesIndex1 = SharedData::grammarList[index1].getRules();
        std::vector<ProductionRule> rulesIndex2 = SharedData::grammarList[index2].getRules();

        for (size_t i = 0; i < rulesIndex1.size(); i++)
        {
            united.addRule(rulesIndex1[i]);
        }

        for (size_t i = 0; i < rulesIndex2.size(); i++)
        {
            united.addRule(rulesIndex2[i]);
        }

        
        
        SharedData::grammarList.push_back(united);
        return newId;
    }
}

std::string GrammarListManager::concat(const std::string& id1, const std::string& id2) //.
{
    int index1 = SharedData::indexOfId(id1);
    int index2 = SharedData::indexOfId(id2);
    
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
            if(SharedData::grammarList[index1].getTerminals(i) || SharedData::grammarList[index2].getTerminals(i))
            {
                concatenated.addLetterToTerminals(i);
            }
        }
        for (size_t i = 0; i < 26; i++)
        {
            if(SharedData::grammarList[index1].getVariable(i) || SharedData::grammarList[index2].getVariable(i))
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
            start += SharedData::grammarList[index1].getStartVariable();
            start += SharedData::grammarList[index2].getStartVariable();
            rules.push_back(start);
            rules.push_back("epsilon");
            ProductionRule newRule(unusedVar, rules);
            concatenated.addRule(newRule);
            newId = concatenated.getId();
        }
        
        std::vector<ProductionRule> rulesIndex1 = SharedData::grammarList[index1].getRules();
        std::vector<ProductionRule> rulesIndex2 = SharedData::grammarList[index2].getRules();

        for (size_t i = 0; i < rulesIndex1.size(); i++)
        {
            concatenated.addRule(rulesIndex1[i]);
        }

        for (size_t i = 0; i < rulesIndex2.size(); i++)
        {
            concatenated.addRule(rulesIndex2[i]);
        }

        
        
        SharedData::grammarList.push_back(concatenated);
        return newId;
    }
}

std::string GrammarListManager::chomsky(const std::string& id) const
{
    int index = SharedData::indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found";
    }
    else
    {
        if(SharedData::grammarList[index].chomsky())
        {
            return "Grammar with id " + id + " is in Chomsky normal form";
        }
        else
        {
            return "Grammar with id " + id + " is not in Chomsky normal form";
        }
        
    }
}

std::string GrammarListManager::cyk(const std::string& id, const std::string& word) 
{
    int index = SharedData::indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found";
    }
    else
    {
        if(!SharedData::grammarList[index].chomsky()){
            
            std::string newId = chomskify(id);
            index = SharedData::indexOfId(newId);
        }
        bool res = SharedData::grammarList[index].cyk(word);
        if(res)
        {
            return "The word " + word + " is recognized by the grammar with id "  + id;
        }
        else
        {
            return "The word " + word + " is not recognized by the grammar with id " + id;
        }
    }
}

std::string GrammarListManager::iter(const std::string& id) //*
{
    int index = SharedData::indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found";
    }
    else
    {
        char unused = unusedVariable(SharedData::grammarList[index]);
        std::string newId = "";
        if(unused != ' ')
        {
            Grammar iter = SharedData::grammarList[index];
            
            iter.addLetterToVariables(unused);
            std::vector<std::string> varRules;
            varRules.push_back("epsilon");
            std::string rule;
            rule.push_back(SharedData::grammarList[index].getStartVariable());
            rule.push_back(unused);
            varRules.push_back(rule);
            iter.addStartVariable(unused);
            ProductionRule newRule(unused, varRules);
            iter.addRule(newRule);

            SharedData::grammarList.push_back(iter);
            newId = iter.getId();
        }
        return newId;
    }
}

std::string GrammarListManager::empty(const std::string& id) const
{
    int index = SharedData::indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found";
    }
    else
    {
        if(SharedData::grammarList[index].isEmpty())
        {
            return "The language of grammar with id " + id + " is empty";
        }
        else
        {
            return "The language of grammar with id " + id + " is not empty";
        }
    }
}

std::string GrammarListManager::chomskify(const std::string& id)
{
    int index = SharedData::indexOfId(id);
    
    if(index == -1) 
    {
        return "Id not found\n";
    }
    else
    {
        if(SharedData::grammarList[index].chomsky())
        {
            return id;
        }
        else
        {
            Grammar newGrammar = SharedData::grammarList[index];
            newGrammar.addStartVariable(newGrammar.getUnusedVariable());
            std::vector<std::string> rule;
            rule.push_back("");
            rule[0].push_back(SharedData::grammarList[index].getStartVariable());
            ProductionRule newStart(newGrammar.getStartVariable(), rule);
            newGrammar.addRule(newStart);
            
            newGrammar.fixRules();

            SharedData::grammarList.push_back(newGrammar);
            return newGrammar.getId();
        }
    }
}

