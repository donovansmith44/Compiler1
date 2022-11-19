#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "CompilationEngine.h"
#include "JackTokenizer.h"

using namespace std;

    CompilationEngine::CompilationEngine(ifstream &jackInput, ofstream &xmlOutput)
    {
        myTokenizer = JackTokenizer(jackInput);
    }
    void CompilationEngine::CompileClass()
    {
        if (myTokenizer.hasMoreTokens()) //class declaration
        {
                myTokenizer.advance();
                cout << "<class>" << endl;
                cout << " <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
                myTokenizer.advance();
                cout << " <identifier> " << myTokenizer.identifier() << " </identifier>" << endl;
                myTokenizer.advance();
                cout << " <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        }

        while (myTokenizer.hasMoreTokens()) //compile classVarDec and subroutineDec
        {
            myTokenizer.advance();
            if (myTokenizer.tokenType() == "KEYWORD")
            {
                if (myTokenizer.keyWord() == "static" | myTokenizer.keyWord() == "field")
                {
                    CompileClassVarDec();
                }
                else if(myTokenizer.keyWord() == "constructor" | myTokenizer.keyWord() == "function" | myTokenizer.keyWord() == "method")
                {
                    CompileSubroutine();
                }
            }            
        }

        cout << " <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        cout << "</class>" << endl;
        return;
    }
    void CompilationEngine::CompileClassVarDec()
    {
        cout << "\n <classVarDec>" << endl;
        cout << "  <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();
        while(myTokenizer.symbol() != ';')
        {
            if (myTokenizer.tokenType() == "KEYWORD")
            {
                cout << "  <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
            }
            else if(myTokenizer.tokenType() == "IDENTIFIER")
            {
                cout << "  <identifier> " << myTokenizer.identifier() << " </identifier>" << endl;
            }
            else if(myTokenizer.symbol() == ',')
            {
                cout << "  <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
            }
            myTokenizer.advance();
        }
        cout << "  <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        cout << " </classVarDec>" << endl;
        return;
    }
    void CompilationEngine::CompileSubroutine()
    {
        cout << "\n <subroutineDec>" << endl;
        cout << "  <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();
        while (myTokenizer.symbol() != ')')
        {
            if (myTokenizer.tokenType() == "KEYWORD")
            {
                cout << "  <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
                myTokenizer.advance();
            }
            else if(myTokenizer.tokenType() == "IDENTIFIER")
            {
                cout << "  <identifier> " << myTokenizer.identifier() << " </identifier>" << endl;
                myTokenizer.advance();
            }
            else if(myTokenizer.symbol() == '(')
            {
                cout << "  <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
                compileParameterList();
            }
        }
        cout << "  <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        /*Compile subroutine body*/
        cout << "  <subroutineBody>" << endl;
        myTokenizer.advance();
        cout << "   <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        while(myTokenizer.symbol() != '}')
        {
            if (myTokenizer.keyWord() == "var")
            {
                compileVarDec();
            }
            compileStatements();
            myTokenizer.advance();
        }
        cout << "   <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        cout << "  </subroutineBody>" << endl;
        cout << " </subroutineDec>" << endl;
        return;
    }
    void CompilationEngine::compileParameterList()
    {
        cout << "   <parameterList> "<< endl;
        while (myTokenizer.symbol() != ')')
        {
            if (myTokenizer.tokenType() == "KEYWORD")
            {
                cout << "    <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
            }
            else if(myTokenizer.tokenType() == "IDENTIFIER")
            {
                cout << "    <identifier> " << myTokenizer.identifier() << " </identifier>" << endl;
            }
            else if(myTokenizer.symbol() == ',')
            {
                cout << "    <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
            }
            myTokenizer.advance();
        }
        cout << "   </parameterList> "<< endl;
        return;
    }
    void CompilationEngine::compileVarDec()
    {
        return;
    }
    void CompilationEngine::compileStatements()
    {
        return;
    }
    void CompilationEngine::compileDo()
    {
        return;
    }
    void CompilationEngine::compileLet()
    {
        return;
    }
    void CompilationEngine::compileWhile()
    {
        return;
    }
    void CompilationEngine::compileReturn()
    {
        return;
    }
    void CompilationEngine::compileIf()
    {
        return;
    }
    void CompilationEngine::CompileExpression()
    {
        return;
    }
    void CompilationEngine::CompileTerm()
    {
        return;
    }