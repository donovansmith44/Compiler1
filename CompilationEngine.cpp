#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "CompilationEngine.h"
#include "JackTokenizer.h"

using namespace std;

    CompilationEngine::CompilationEngine(ifstream &jackInput, ofstream &xmlOutput){
        jackInput.open("file.txt");
        string line;
        while(getline(jackInput, line))
        {
            cout << line << endl;
        }
    }
    void CompilationEngine::CompileClass(){
        return;
    }
    void CompilationEngine::CompileClassVarDec(){
        return;
    }
    void CompilationEngine::CompileSubroutine(){
        return;
    }
    void CompilationEngine::compileParameterList(){
        return;
    }
    void CompilationEngine::compileVarDec(){
        return;
    }
    void CompilationEngine::compileStatements(){
        return;
    }
    void CompilationEngine::compileDo(){
        return;
    }
    void CompilationEngine::compileLet(){
        return;
    }
    void CompilationEngine::compileWhile(){
        return;
    }
    void CompilationEngine::compileReturn(){
        return;
    }
    void CompilationEngine::compileIf(){
        return;
    }
    void CompilationEngine::CompileExpression(){
        return;
    }
    void CompilationEngine::CompileTerm(){
        return;
    }