#include "EmployeeInfoManager.h"

using namespace std;

string EmployeeInfoManager::ExcuteCommand(string singleCmdString) {
    vector<string> parsedCommand = commandParser.parseCommand(singleCmdString);
    string result;
    
    result = commandList[parsedCommand[OP_COMMAND_IDX]]->runCmd(employeeList, parsedCommand);

    return result;
};

void EmployeeInfoManager::Run(string inputfile, string outputfile) {
    if (!fileController.open(inputfile, inputfile)) return;

    string command;
    while ((command = fileController.getCommand()) != "") {
        ExcuteCommand(command);
        fileController.writeCommandResult(command);
    } 
    fileController.close();
}