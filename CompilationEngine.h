#ifndef COMPILATION_ENGINE
#define COMPILATION_ENGINE

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "JackTokenizer.h"

using namespace std;

class CompilationEngine{
    public:
    CompilationEngine();
    CompilationEngine(ifstream&, ofstream&);
    void CompileClass();
    void CompileClassVarDec();
    void CompileSubroutine();
    void compileParameterList();
    void compileVarDec();
    void compileStatements();
    void compileDo();
    void compileLet();
    void compileWhile();
    void compileReturn();
    void compileIf();
    void CompileExpression();
    void CompileTerm();
    private:
    ifstream _jackInput;
    ofstream _xmlOutput;
};


#endif
