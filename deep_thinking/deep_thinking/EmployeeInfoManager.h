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
    // NOTE, multimap pair<key, value = employNum>
    multimap<string, string> fullNameMap;
    multimap<string, string> firstNameMap;
    multimap<string, string> levelMap;
    multimap<string, string> lastNameMap;
    multimap<string, string> phoneNumMap;
    multimap<string, string> phoneMidNumMap;
    multimap<string, string> phoneLastNumMap;
    multimap<string, string> birthDateMap;
    multimap<string, string> birthYearMap;
    multimap<string, string> birthMonthMap;
    multimap<string, string> birthDayMap;
    multimap<string, string> certiMap;

    const int OP_COMMAND_IDX = 0;
};
