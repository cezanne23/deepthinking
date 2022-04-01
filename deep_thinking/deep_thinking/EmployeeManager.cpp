#include "EmployeeManager.h"

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
