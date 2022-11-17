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
    vector<string> jackFiles = getJackFiles(argv[1]);
    
    ifstream jackFile;
    ofstream xmlFile;
    for (int i = 0; i < jackFiles.size(); i++)
    {
        cout << "\n**************NEXT CLASS**************\n" << endl;
        jackFile.open(jackFiles[i]);
        CompilationEngine parser(jackFile, xmlFile);
        jackFile.close();
    }

    return 0;
}