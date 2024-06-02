# context-free-grammar

## Commands for compiling the code

1. Default
```markdown
g++ -o program.out main.cpp ProductionRule/productionRule.cpp HelperFunctions/helperFunctions.cpp Grammar/grammar.cpp Engine/engine.cpp FileManager/fileManager.cpp GrammarListManager/grammarListManager.cpp SharedData/sharedData.cpp 
```
```markdown
./program.out
```
2. With test
```markdown
g++ -o test.out ProductionRule/productionRule.cpp HelperFunctions/helperFunctions.cpp Grammar/grammar.cpp Engine/engine.cpp FileManager/fileManager.cpp GrammarListManager/grammarListManager.cpp SharedData/sharedData.cpp Tests/TESTFILE
```
```markdown
./test.out
```
## TESTFILE replacements
- Tests/engine_test.cpp
- Tests/fileManager_test.cpp
- Tests/grammar_test.cpp
- Tests/grammarListManager_test.cpp
- Tests/helperFunctions_test.cpp
- Tests/productionRule_test.cpp
- Tests/sharedData_test.cpp