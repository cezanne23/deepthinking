#include "EmployeeInfoManager.h"

using namespace std;

EmployeeInfoManager::EmployeeInfoManager() {
    AddCommand* addCommand = new AddCommand();
    DeleteCommand* deleteCommand = new DeleteCommand();
    ModifyCommand* modifyCommand = new ModifyCommand();
    SearchCommand* searchCommand = new SearchCommand();

    commands.push_back(addCommand);
    commands.push_back(deleteCommand);
    commands.push_back(modifyCommand);
    commands.push_back(searchCommand);
}
string EmployeeInfoManager::ExcuteCommand(string singleCmdString) {
    vector<string> parsedCommand = commandParser.parseCommand(singleCmdString);

    // todo : 다형성 적용 필요 (Command Parser로 이동)
    if (parsedCommand[OP_COMMAND_IDX] == "ADD")
    {
        commands[ADD_COMMAND_IDX]->runCmd(employeeList, parsedCommand);
    }
    else if (parsedCommand[OP_COMMAND_IDX] == "DEL")
    {
        commands[DEL_COMMAND_IDX]->runCmd(employeeList, parsedCommand);
    }
    else if (parsedCommand[OP_COMMAND_IDX] == "MOD")
    {
        commands[MOD_COMMAND_IDX]->runCmd(employeeList, parsedCommand);
    }
    else if (parsedCommand[OP_COMMAND_IDX] == "SCH")
    {
        commands[SCH_COMMAND_IDX]->runCmd(employeeList, parsedCommand);
    }

    return "ExcuteCommand";
};