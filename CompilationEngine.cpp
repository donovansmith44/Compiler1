#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "CompilationEngine.h"
#include "JackTokenizer.h"

using namespace std;

    CompilationEngine::CompilationEngine(ifstream &jackInput, ofstream &xmlOutput){
        JackTokenizer myTokenizer(jackInput);
    
        cout << "Begin tokenization:" << endl;

        while(myTokenizer.hasMoreTokens()){
            myTokenizer.advance();

            if (myTokenizer.tokenType() == "KEYWORD")
            {
                myTokenizer.keyWord();
                cout << myTokenizer.tokenType() << ": " << myTokenizer.keyWord() << endl;
            }
            else if (myTokenizer.tokenType() == "SYMBOL")
            {
                myTokenizer.symbol();
                cout << myTokenizer.tokenType() << ": " << myTokenizer.symbol() << endl;
            }
            else if (myTokenizer.tokenType() == "INT_CONST")
            {
                myTokenizer.intVal();
                cout << myTokenizer.tokenType() << ": " << myTokenizer.intVal() << endl;
            }
            else if (myTokenizer.tokenType() == "STRING_CONST")
            {
                myTokenizer.stringVal();
                cout << myTokenizer.tokenType() << ": " << myTokenizer.stringVal() << endl;
            }
            else if (myTokenizer.tokenType() == "IDENTIFIER")
            {
                myTokenizer.identifier();
                cout << myTokenizer.tokenType() << ": " << myTokenizer.identifier() << endl;
            }
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