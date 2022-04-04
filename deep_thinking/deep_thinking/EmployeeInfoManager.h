#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "Command.h"
#include "CommandParser.h"
using namespace std;

class EmployeeInfoManager {
public:
    EmployeeInfoManager() {
        commandList.insert({ "ADD", new AddCommand() });
        commandList.insert({ "DEL", new DeleteCommand() });
        commandList.insert({ "MOD", new ModifyCommand() });
        commandList.insert({ "SCH", new SearchCommand() });
    }
    string ExcuteCommand(string singleCmdString);

private:
    map<string, EmployeeInfo> employeeList;
    CommandParser commandParser;
    map<string, ICommand*> commandList;

    const int OP_COMMAND_IDX = 0;
};
