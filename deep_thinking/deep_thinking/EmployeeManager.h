#pragma once

#include <string>
using namespace std;

class EmployeeManager {
public:
    bool setFilePath(string inputfile, string outputfile);
    const bool isVaildFilePath(string filepath) const;

private:
    const string fileExtension(string filepath) const;
    string intputfile_;
    string outputfile_;
};