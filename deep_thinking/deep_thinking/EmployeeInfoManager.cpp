#include "EmployeeInfoManager.h"

using namespace std;

string EmployeeInfoManager::ExcuteCommand(string singleCmdString) {
    vector<string> parsedCommand = commandParser.parseCommand(singleCmdString);
    string result;
    
    result = commandList[parsedCommand[OP_COMMAND_IDX]]->runCmd(employeeList, parsedCommand);

    return result;
};