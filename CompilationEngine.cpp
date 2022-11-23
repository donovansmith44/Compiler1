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
    void CompilationEngine::compileClass()
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
                    compileClassVarDec();
                }
                else if(myTokenizer.keyWord() == "constructor" | myTokenizer.keyWord() == "function" | myTokenizer.keyWord() == "method")
                {
                    compileSubroutine();
                }
            }            
        }

        cout << " <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        cout << "</class>" << endl;
        return;
    }
    void CompilationEngine::compileClassVarDec()
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
    void CompilationEngine::compileSubroutine()
    {
        cout << "\n <subroutineDec>" << endl;
        cout << "  <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();

        cout << "  <keyword> " << myTokenizer.keyWord() << " </keyword>" << endl;
        myTokenizer.advance();

        cout << "  <identifier> " << myTokenizer.identifier() << " </identifier>" << endl;
        myTokenizer.advance();

        cout << "  <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        myTokenizer.advance();
        compileParameterList();

        cout << "  <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;

        /*compile subroutine body*/
        cout << "  <subroutineBody>" << endl;
        myTokenizer.advance();
        cout << "   <symbol> " << myTokenizer.symbol() << " </symbol>" << endl;
        
        myTokenizer.advance();
        while (myTokenizer.keyWord() == "var")
        {
            compileVarDec();
            myTokenizer.advance();
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
            if (myTokenizer.keyWord() == "let") //the currentToken should be ';' after the let statement compiles
            {
                compileLet();
                myTokenizer.advance();
            }
            else if (myTokenizer.keyWord() == "if") //the currentToken should be the first token after the statement's closing '}' after the if statement compiles
            {
                compileIf();
                
            }
            else if (myTokenizer.keyWord() == "do") //the currentToken should be ';' after the do statement compiles
            {
                compileDo();
                myTokenizer.advance();
            }
            else if (myTokenizer.keyWord() == "while") //the currentToken should be '}' after the while statement compiles
            {
                compileWhile();
                myTokenizer.advance();
            }
            else if (myTokenizer.keyWord() == "return") //the currentToken should be ';' after the return statement compiles
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
        
        cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>"  << endl;
        myTokenizer.advance();

            /*SUBROUTINE CALL*/
            if (myTokenizer.tokenType() == "IDENTIFIER")
            {
                cout << "     <identifier> " << myTokenizer.identifier() << " </identifier>"  << endl; //subroutineName
                myTokenizer.advance();
                
                if(myTokenizer.symbol() == '.') // '.' subRoutine Name '(' expressionList ')'
                {
                    cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '.'
                    myTokenizer.advance();

                    cout << "     <identifier> " << myTokenizer.identifier() << " </identifier>"  << endl; //subroutineName
                    myTokenizer.advance();
                }

                    cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '('
                    myTokenizer.advance();
                    
                    compileExpressionList();

                    cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // ')'
                    myTokenizer.advance();
            }

            cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // ';'
            
            cout << "    </doStatement> " << endl;
        return;
    }
    void CompilationEngine::compileLet()
    {
        cout << "    <letStatement> " << endl;
        
        cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>"  << endl;
        myTokenizer.advance();
            
        cout << "     <identifier> " << myTokenizer.identifier() << " </identifier>"  << endl; //subroutineName
        myTokenizer.advance();

        if (myTokenizer.symbol() == '[')
        {
            cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '['
            myTokenizer.advance();

            compileExpression();
            myTokenizer.advance();
            
            cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // ']'
            myTokenizer.advance();
        }
        
        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '='
        myTokenizer.advance();

        compileExpression();
        myTokenizer.advance();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // ';'

        cout << "    </letStatement> " << endl;
        return;
    }
    void CompilationEngine::compileWhile()
    {
        cout << "    <whileStatement> " << endl;
        
        cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>"  << endl;
        myTokenizer.advance();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '('
        myTokenizer.advance();

        compileExpression();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // ')'
        myTokenizer.advance();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '{'
        myTokenizer.advance();

        compileStatements();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '}'
        
        cout << "    </whileStatement> " << endl;
        return;
    }
    void CompilationEngine::compileReturn()
    {
        cout << "    <returnStatement> " << endl;
        
        cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>"  << endl;
        myTokenizer.advance();

        if (myTokenizer.symbol() != ';')
        {
            compileExpression();
            myTokenizer.advance();    
        }

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // ';'

        cout << "    </returnStatement> " << endl;
        return;
    }
    void CompilationEngine::compileIf()
    {
        cout << "    <ifStatement> " << endl;
        
        cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>"  << endl;
        myTokenizer.advance();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '('
        myTokenizer.advance();

        compileExpression();
        myTokenizer.advance();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // ')'
        myTokenizer.advance();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '{'
        myTokenizer.advance();

        compileStatements();

        cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '}'
        myTokenizer.advance();

        if (myTokenizer.keyWord() == "else")
        {
            cout << "     <keyword> " << myTokenizer.keyWord() << " </keyword>"  << endl;
            myTokenizer.advance();
            
            cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '{'
            myTokenizer.advance();

            compileStatements();

            cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '}'
            myTokenizer.advance();
        }

        cout << "    </ifStatement> " << endl;
        return;
    }
    void CompilationEngine::compileExpression()
    {
        cout << "      <expression> " << endl;
        
        compileTerm();
        
        if (myTokenizer.getNext() == "+" | myTokenizer.getNext() == "-" | myTokenizer.getNext() == "*" | myTokenizer.getNext() == "/" | myTokenizer.getNext() == "&" | myTokenizer.getNext() == "|" | myTokenizer.getNext() == "<" | myTokenizer.getNext() == ">" | myTokenizer.getNext() == "=")
        {
            myTokenizer.advance();
            cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // op
            myTokenizer.advance();
            compileTerm();   
        }
        cout << "      </expression> " << endl;

        return;
    }

    void CompilationEngine::compileTerm()
    {
        string tempToken = "";
        cout << "       <term> " << endl;
        if (myTokenizer.tokenType() == "INT_CONST")
        {
            cout << "      <integerConstant> " << myTokenizer.intVal() << " </integerConstant> " << endl;
        }
        else if (myTokenizer.tokenType() == "STRING_CONST")
        {
            cout << "      <stringConstant> " << myTokenizer.stringVal() << " </stringConstant> " << endl;
        }
        else if (myTokenizer.keyWord() == "true" | myTokenizer.keyWord() == "false" | myTokenizer.keyWord() == "null"  | myTokenizer.keyWord() == "this" )
        {
            cout << "      <keyword> " << myTokenizer.keyWord() << " </keyword> " << endl;
        }
        else if (myTokenizer.tokenType() == "IDENTIFIER")
        {
            cout << "      <identifier> " << myTokenizer.identifier() << " </identifier> " << endl;

            if (myTokenizer.getNext() == "[" | myTokenizer.getNext() == "(")
            {
                myTokenizer.advance();
                
                cout << "      <symbol> " << myTokenizer.symbol() << " </symbol> " << endl; // '(' | '['
                myTokenizer.advance();

                compileExpression();

                myTokenizer.advance();
                
                cout << "      <symbol> " << myTokenizer.symbol() << " </symbol> " << endl; // ')' | ']'
            }
            else if(myTokenizer.getNext() == ".") //subroutineCall
            {
                myTokenizer.advance();
                cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '.'
                myTokenizer.advance();

                cout << "     <identifier> " << myTokenizer.identifier() << " </identifier>"  << endl; //subroutineName
                myTokenizer.advance();
            

                cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // '('
                myTokenizer.advance();
                
                compileExpressionList();

                cout << "     <symbol> " << myTokenizer.symbol() << " </symbol>"  << endl; // ')'
            }
        }
        else if (myTokenizer.symbol() == '-' || myTokenizer.symbol() == '~') //unaryop term
        {
            cout << "      <symbol> " << myTokenizer.symbol() << " </symbol> " << endl;
            myTokenizer.advance();
            compileTerm();
        }
        else if (myTokenizer.symbol() == '(') //'(' expression ')'
        {
            cout << "      <symbol> " << myTokenizer.symbol() << " </symbol> " << endl;
            myTokenizer.advance();
            compileExpression();
            myTokenizer.advance();
            cout << "      <symbol> " << myTokenizer.symbol() << " </symbol> " << endl;
        }        
        cout << "       </term>" << endl;
        
        return;
    }
    void CompilationEngine::compileExpressionList()
    {
        cout << "<expressionList> " << endl;
        
        cout << " </expressionList>" << endl;
        return;
    }