#include "EmployeeManager.h"

#include <fstream>
#include <iostream>

const string EmployeeManager::fileExtension(string filepath) const {
    if (filepath.find_last_of(".") != std::string::npos)
        return filepath.substr(filepath.find_last_of(".") + 1);
    return "";
}

bool EmployeeManager::setFilePath(const string& inputfile, const string& outputfile) {
    if (!isVaildFilePath(inputfile)) return false;
    if (!isVaildFilePath(outputfile)) return false;

    intputfile_ = inputfile;
    outputfile_ = outputfile;
    return true;
}

const bool EmployeeManager::isVaildFilePath(string filepath) const {
    if (filepath.find("./") != string::npos) return false;
    if (fileExtension(filepath) != "txt") return false;

    return true;
}

vector<string> EmployeeManager::execute() {
    ifstream inputfile(intputfile_);

    // TODO : integration EmployeeInforManager - TDD checking
    vector<string> lines;
    string line;
    //
    if (!inputfile.is_open()) {
        cerr << "Could not open the file !! " << intputfile_ << "'" << endl;
        throw std::invalid_argument("it's invalid filePath");
    }

    int count = 0;
    while (std::getline(inputfile, line) && count < 10) {
        // TODO : integration EmployeeInforManager - TDD  checking
        lines.push_back(line);
        count++;
        //
        // TOBE: ofstream && writeCommandResult(ouput_file, ..); 
    }

    inputfile.close();
    return lines;
}

void EmployeeManager::writeCommandResult(ofstream& ouptputfile, string result) {
    ouptputfile << result << endl;
}