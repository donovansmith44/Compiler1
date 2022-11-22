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
        
        myTokenizer.advance();
        if (myTokenizer.keyWord() == "var")
        {
            compileVarDec();
        }
        compileStatements();

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
        cout << "    <varDec> " << endl;
        cout << "     <keyWord> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();
        while (myTokenizer.symbol() != ';')
        {
            if (myTokenizer.tokenType() == "KEYWORD")
            {
                cout << "     <keyWord> " << myTokenizer.keyWord() << " </keyword>" << endl;
            }
            else if (myTokenizer.tokenType() == "SYMBOL")
            {
                cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
            }
            else if (myTokenizer.tokenType() == "IDENTIFIER")
            {
                cout << "     <identifier> " << myTokenizer.identifier() << " </identifier>" << endl;
            }
            myTokenizer.advance();
        }
        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        cout << "    </varDec> " << endl;
        return;
    }
    void CompilationEngine::compileStatements()
    {
        cout << "   <statements> " << endl;
        while (myTokenizer.symbol() != '}')
        {
            if (myTokenizer.keyWord() == "let")
            {
                compileLet();
                myTokenizer.advance();
            }
            else if (myTokenizer.keyWord() == "if")
            {
                compileIf();
                myTokenizer.advance();
            }
            else if (myTokenizer.keyWord() == "do")
            {
                compileDo();
                myTokenizer.advance();
            }
            else if (myTokenizer.keyWord() == "while")
            {
                compileWhile();
                myTokenizer.advance();
            }
            else if (myTokenizer.keyWord() == "return")
            {
                compileReturn();
                myTokenizer.advance();
            }
            else if (myTokenizer.keyWord() == "var")
            {
                compileVarDec();
                myTokenizer.advance();
            }
            else
            {
                myTokenizer.advance();
            }
        }
        cout << "   </statements> " << endl;
        return;
    }
    void CompilationEngine::compileDo()
    {
        cout << "    <doStatement> " << endl;
        cout << "     <keyword> " << myTokenizer.keyWord() << "</keyword>" << endl;
        
        myTokenizer.advance();

        while (myTokenizer.symbol() != '(')
        {
            if (myTokenizer.tokenType() == "KEYWORD")
            {
                cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
                myTokenizer.advance();
            }
            else if (myTokenizer.tokenType() == "SYMBOL")
            {
                cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
                myTokenizer.advance();
            }
            else if (myTokenizer.tokenType() == "IDENTIFIER")
            {
                cout << "     <identifier> " << myTokenizer.identifier() << " </identifier>" << endl;
                myTokenizer.advance();
            }
            else
            {
                myTokenizer.advance();
            }
        }

        CompileExpression();
        myTokenizer.advance();
        if (myTokenizer.symbol() == ';')
        {
            cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        }
        
        cout << "    </doStatement> " << endl;
        return;
    }
    void CompilationEngine::compileLet()
    {
        cout << "    <letStatement> " << endl;
        cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();

        cout << "    </letStatement> " << endl;
        return;
    }
    void CompilationEngine::compileWhile()
    {
        cout << "    <whileStatement> " << endl;
        cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();
        while (myTokenizer.symbol() !='}')
        {
            if (myTokenizer.tokenType() == "SYMBOL")
            {
                if (myTokenizer.symbol() == '(')
                {
                    //cout << "      <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
                    CompileExpression();
                    myTokenizer.advance();
                }
                else if(myTokenizer.symbol() == '{')
                {
                    cout << "      <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
                    compileStatements();
                    myTokenizer.advance();
                }
                else
                {
                    myTokenizer.advance();
                }
            }
            else
            {
                myTokenizer.advance();
            }
        }
        cout << "      <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        cout << "    </whileStatement> " << endl;
        return;
    }
    void CompilationEngine::compileReturn()
    {
        cout << "    <returnStatement> " << endl;
        cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();
        while (myTokenizer.symbol() !=';')
        {
            myTokenizer.advance();
        }
        cout << "     <symbol> " << myTokenizer.keyWord() << " </symbol>" << endl;
        cout << "    </returnStatement> " << endl;
        return;
    }
    void CompilationEngine::compileIf()
    {
        cout << "    <ifStatement> " << endl;
        cout << "      <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();
        CompileExpression();
        myTokenizer.advance();
        cout << "      <symbol> " << myTokenizer.keyWord() << " </symbol>" << endl;
        myTokenizer.advance();
        compileStatements();
        cout << "      <symbol> " << myTokenizer.keyWord() << " </symbol>" << endl;
        myTokenizer.advance();
        if (myTokenizer.keyWord() == "else")
        {
            cout << "      <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
            myTokenizer.advance();
            cout << "      <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
            myTokenizer.advance();
            compileStatements();
            cout << "      <symbol> " << myTokenizer.keyWord() << " </symbol>" << endl;
        }
        cout << "      <symbol> " << myTokenizer.keyWord() << " </symbol>" << endl;
        cout << "    </ifStatement> " << endl;
        return;
    }
    void CompilationEngine::CompileExpression()
    {
        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        myTokenizer.advance();
        cout << "      <expressionList> " << endl;
        while (myTokenizer.symbol() != ')')
        {
            if (myTokenizer.tokenType() == "KEYWORD")
            {
                cout << "      <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
                myTokenizer.advance();
            }
            else if (myTokenizer.tokenType() == "SYMBOL")
            {
                cout << "       <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
                myTokenizer.advance();
            }
            else if (myTokenizer.tokenType() == "IDENTIFIER")
            {
                cout << "       <identifier> " << myTokenizer.identifier() << " </identifier>" << endl;
                myTokenizer.advance();
            }
            else
            {
                myTokenizer.advance();
            }
        }
        cout << "      </expressionList> " << endl;
        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        return;
    }
    void CompilationEngine::CompileTerm()
    {
        if (myTokenizer.tokenType() == "INT_CONST")
        {
            /* code */
        }
        else if (myTokenizer.tokenType() == "STRING_CONST")
        {
            /* code */
        }
        if (myTokenizer.keyWord() == "true" || myTokenizer.keyWord() == "false" || myTokenizer.keyWord() == "null" || myTokenizer.keyWord() == "this")
        {
            /* code */
        }
        
        return;
    }