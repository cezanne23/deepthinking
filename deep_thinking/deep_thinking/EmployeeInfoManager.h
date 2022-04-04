#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "Command.h"
#include "CommandParser.h"
using namespace std;

class EmployeeInfoManager {
public:
    EmployeeInfoManager();
    string ExcuteCommand(string singleCmdString);

private:
    vector<ICommand*> commands;
    CommandParser commandParser;
    map<string, EmployeeInfo> employeeList;

    const int OP_COMMAND_IDX = 0;

    // todo : 다형성 적용후 삭제 되어야 함
    const int ADD_COMMAND_IDX = 0;
    const int DEL_COMMAND_IDX = 1;
    const int MOD_COMMAND_IDX = 2;
    const int SCH_COMMAND_IDX = 3;
};
