#pragma once

#include <string>
#include <vector>
using namespace std;

class EmployeeManager {
public:
    bool setFilePath(const string& inputfile, const string& outputfile);
    const bool isVaildFilePath(string filepath) const;

    vector<string> execute();
    void writeCommandResult(ofstream& ouptputfile, string result);
private:
    const string fileExtension(string filepath) const;
    string intputfile_;
    string outputfile_;
};