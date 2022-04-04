#include "FileController.h"

const string FileController::fileExtension(string filepath) const {
    if (filepath.find_last_of(".") != std::string::npos)
        return filepath.substr(filepath.find_last_of(".") + 1);
    return "";
}

bool FileController::open(const string& inputfile, const string& outputfile) {
    if (!isVaildFilePath(inputfile)) return false;
    if (!isVaildFilePath(outputfile)) return false;

    inputfileStream = ifstream(inputfile);
    outputfileStream = ofstream(outputfile);

    if (!inputfileStream.is_open()) {
        cerr << "Could not open the file !! " << inputfile << "'" << endl;
        throw std::invalid_argument("it's invalid filePath");
    }

    if (!outputfileStream.is_open()) {
        cerr << "Could not open the file !! " << outputfile << "'" << endl;
        throw std::invalid_argument("it's invalid filePath");
    }
    return true;
}

void FileController::close() {
    inputfileStream.close();
    outputfileStream.close();
}

const bool FileController::isVaildFilePath(string filepath) const {
    if (filepath.find("./") != string::npos) return false;
    if (fileExtension(filepath) != "txt") return false;

    return true;
}

string FileController::getCommand() {
    string line;

    if (std::getline(inputfileStream, line)) return line;
    return "";
}

void FileController::writeCommandResult(string result) {
    outputfileStream << result << endl;
}