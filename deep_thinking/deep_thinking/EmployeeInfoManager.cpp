#include "EmployeeInfoManager.h"

using namespace std;

string EmployeeInfoManager::ExcuteCommand(string singleCmdString) {
    vector<string> parsedCommand = commandParser.parseCommand(singleCmdString);
    string result;

    result = commandList[parsedCommand[OP_COMMAND_IDX]]->runCmd(parsedCommand);

    return result;
};

void EmployeeInfoManager::Run(string inputfile, string outputfile) {
    if (!fileController.open(inputfile, outputfile)) return;

    string command;
    while ((command = fileController.getCommand()) != "") {
        string result = ExcuteCommand(command);
        if (result != "") fileController.writeCommandResult(result);
    }
    fileController.close();
}