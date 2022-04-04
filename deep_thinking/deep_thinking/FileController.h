#pragma once

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class FileController {
public:
    bool open(const string& inputfile, const string& outputfile);
    void close();
    string getCommand();
    void writeCommandResult(string result);

    const bool isVaildFilePath(string filepath) const;
private:
    const string fileExtension(string filepath) const;
    ifstream inputfileStream;
    ofstream outputfileStream;
};