#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cctype>
#include "JackTokenizer.h"
#include "CompilationEngine.h"

using namespace std;

JackTokenizer::JackTokenizer(string fileName)
{
        string line;
        commandNum = 0;
        currentToken = "";

        jackFile.open(fileName);
        
        while(getline(jackFile, line)) //we store all of the lines of Jack code into a vector
        {
            jackLines.push_back(line);
        }

        clean(); //remove comments and whitespace from input stream, and parse all of the code into individual tokens
}

bool JackTokenizer::hasMoreTokens()
{
    if (commandNum < jackTokens.size())
    {
        return true;
    }
    return false;
}
void JackTokenizer::advance()
{
    currentToken = jackTokens[commandNum];
    commandNum++;
    return;
}
string JackTokenizer::tokenType()
{
    if (isKeyword(currentToken))
    {
        return "KEYWORD";
    }
    else if (isSymbol(currentToken))
    {
        return "SYMBOL";
    }
    else if (currentToken.find('"') != string::npos)
    {
        return "STRING_CONST";
    }
    else if(isIntConstant(currentToken))
    {
        return "INT_CONST";
    }
    else
    {
        return "IDENTIFIER";
    }
}
string JackTokenizer::keyWord()
{
    return currentToken;
}
char JackTokenizer::symbol()
{
    return currentToken[0];
}
string JackTokenizer::identifier()
{  
    return currentToken;
}
int JackTokenizer::intVal()
{
    return stoi(currentToken);
}
string JackTokenizer::stringVal()
{
    return currentToken.substr(1, currentToken.length()-2); //ignore double quotes
}
vector<string> JackTokenizer::removeLineComments(vector<string> tokens)
{
    vector<string> newTokens;
    for (int i = 0; i < tokens.size(); i++)
    {
        if(tokens[i].find("//") != string::npos)
        {
            tokens[i].erase(tokens[i].find("//"), tokens[i].length()-tokens[i].find("//")); //ignore all characters following "//" during compile time
        }
        if (!tokens[i].empty() && tokens[i] != " ")
        {
            newTokens.push_back(tokens[i]);
        }   
    }
    
    return newTokens;
}
vector<string> JackTokenizer::removeAPIComments(vector<string> tokens)
{
    vector<string> newTokens;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].find("/**") != string::npos)
        {
            for (int j = i; j < tokens.size(); j++)
            {
                if (tokens[j].find("*/") == string::npos)
                {
                    tokens[j] = "";
                }
                else
                {
                    tokens[j].erase(0, tokens[j].find("*/")+2);
                    break;
                }
            }
        }
        if (!tokens[i].empty() && tokens[i] != " ")
        {
            newTokens.push_back(tokens[i]);
        }
    }

    return newTokens;
}
vector<string> JackTokenizer::removeBlockComments(vector<string> tokens)
{
    vector<string> newTokens;

    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].find("/*") != string::npos)
        {
            for (int j = i; j < tokens.size(); j++)
            {
                if (tokens[j].find("*/") == string::npos)
                {
                    tokens[j] = "";
                }
                else
                {
                    tokens[j].erase(0, tokens[j].find("*/")+2);
                    break;
                }
            }
        }
        if (!tokens[i].empty() && tokens[i] != " ")
        {
            newTokens.push_back(tokens[i]);
        }
    }
    
    return newTokens;
}
vector<string> JackTokenizer::appendStringLiterals(vector<string> tokens)
{
    string temp = "";
    for (int i = 0; i < tokens.size(); i++)
    {
        temp = tokens[i];
        if (temp.find('"') != string::npos)
        {
            for (int j = i+1; j < tokens.size(); j++)
            {
                if(tokens[j].find('"') != string::npos)
                {
                    temp += " " + tokens[j];
                    tokens[i] = temp;
                    tokens.erase(tokens.begin() + j);
                    break;
                }
                else
                {
                    temp += " " + tokens[j];
                    tokens.erase(tokens.begin() + j);
                }
            }   
        }
    }
       
    return tokens;
}
bool JackTokenizer::isKeyword(string line)
{
    if (line == "class" || line == "constructor" || line == "function" || line == "method" || line == "field" || line == "static" || line == "var" || line == "int" || line == "char" || line == "boolean" || line == "void" || line == "true" || line == "false" || line == "null" || line == "this" || line == "let" || line == "do" || line == "if" || line == "else" || line == "while" || line == "return")
    {
        return true;
    }
    return false;
}
bool JackTokenizer::isSymbol(string line)
{
    if(line == "{" || line == "}" || line == "(" || line == ")" || line == "[" || line == "]" || line == "." || line == "," || line == ";" || line == "+" || line == "-" || line == "*" || line == "/" || line == "&" || line == "|" || line == "<" || line == ">" || line == "=" || line == "~")
    {
        return true;
    }
    return false;
}
bool JackTokenizer::isIntConstant(string line)
{
    for (int i = 0; i < line.length(); i++)
    {
        if (!isdigit(line[i])) //if any of the characters in the string aren't digits, the string isn't a number.
        {
            return false;
        }
    }
    return true;
}
void JackTokenizer::clean() //remove comments and unnecessary whitespace lines
{
    string allLines = "";
    jackLines = removeLineComments(jackLines);
    jackLines = removeAPIComments(jackLines);
    jackLines = removeBlockComments(jackLines);
    
    for (int i = 0; i < jackLines.size(); i++) //concatenate all of the cleaned lines into a single string to be split into unique tokens
    {
        allLines += jackLines[i];
    }
    
    jackTokens = Tokenize(allLines);
    
    return;
}
vector<string> JackTokenizer::Tokenize(string line)
{
    int i = 0;
    string tempString = "";
    vector<string> tokens;

    for (int i = 0; i < line.length(); i++)
    {
        if (!isSymbol(line.substr(i+1, 1)) && line.substr(i+1, 1) != " ") //if the i+1th character is not a symbol or space
        {
            if (!isspace(line[i])) //iteratively add all non space characters into a temporary string variable, and check if it becomes a unique token
            {
                tempString += line[i];
                if (isKeyword(tempString))
                {
                    tokens.push_back(tempString);
                    tempString = "";
                }
                else if(isSymbol(tempString))
                {
                    tokens.push_back(tempString);
                    tempString = "";
                }
            }
        }
        else //if the i+1th character is a symbol or space, then save all of the non-space characters up to that symbol as a new token.
        {
            tempString += line[i];

                if (tempString != " " && !tempString.empty())
                {
                    tokens.push_back(tempString);
                }

            tempString = "";
        }
        
    }

    tokens = appendStringLiterals(tokens); //string constants must be treated differently because they include double quotes, and may span multiple tokens (in the way I've chosen to parse them here)

    for (int i = 0; i < tokens.size(); i++) //remove the blank elements from the vector
    {
        string temp = tokens[i];
        if (isspace(temp[0]))
        {
            tokens.erase(tokens.begin() + i);
        }    
    }
    
    return tokens;
}
