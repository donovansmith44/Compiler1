#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include "JackTokenizer.h"
#include "CompilationEngine.h"

using namespace std;

vector<string> getJackFiles(string directoryName)
{
    vector<string> files;

    std::string path(directoryName);

    std::string ext(".jack");

    for(auto &p : std::filesystem::recursive_directory_iterator(path))
    {
        if(p.path().extension() == ext)
        {
            files.push_back(directoryName + "/" + p.path().stem().string() + ".jack");
        }
    }
    return files;
}

int main(int argc, char* argv[]){
    vector<string> jackFiles;

    jackFiles = getJackFiles(argv[1]);
    
    ifstream jackFile;
    ofstream xmlFile;

    JackTokenizer tokenizer(jackFiles[2]);

    CompilationEngine parser(jackFile, xmlFile);

    cout << "Begin tokenization:" << endl;
    while(tokenizer.hasMoreTokens()){
    tokenizer.advance();

    if (tokenizer.tokenType() == "KEYWORD")
    {
        tokenizer.keyWord();
        cout << tokenizer.tokenType() << ": " << tokenizer.keyWord() << endl;
    }
    else if (tokenizer.tokenType() == "SYMBOL")
    {
        tokenizer.symbol();
        cout << tokenizer.tokenType() << ": " << tokenizer.symbol() << endl;
    }
    else if (tokenizer.tokenType() == "INT_CONST")
    {
        tokenizer.intVal();
        cout << tokenizer.tokenType() << ": " << tokenizer.intVal() << endl;
    }
    else if (tokenizer.tokenType() == "STRING_CONST")
    {
        tokenizer.stringVal();
        cout << tokenizer.tokenType() << ": " << tokenizer.stringVal() << endl;
    }
    else if (tokenizer.tokenType() == "IDENTIFIER")
    {
        tokenizer.identifier();
        cout << tokenizer.tokenType() << ": " << tokenizer.identifier() << endl;
    }
    }
    return 0;
}