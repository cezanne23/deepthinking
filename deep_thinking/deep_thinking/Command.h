#pragma once
#include <iostream>
#include <map>
#include "SearchEngine.h"
#include "CommandParser.h"
#include "EmployeeDB.h"
#include "Sorting.h"

using namespace std;

class ICommand {
public:
    ICommand() : employeeDB(EmployeeDB::getDB()) {
    }
    virtual string runCmd(vector<string>& command) = 0;
    const int CMD_DISPLAY_RECORD = 1;
    string convertToString(vector<string> strList) {
        string result;
        for (const auto& str : strList) {
            result += str + "\n";
        }
        return result.substr(0, result.size() - 1);
    }

    vector<string> displayEmployeeInfo(vector<string> list, string cmdType) {
        vector<EmployeeInfo> infoList;
        vector<string> displayRecord;
        for (const auto& employeeNum : list) {
            infoList.push_back(employeeDB->employeeList[employeeNum]);
        }
        priorityQueue.sort(infoList);

        for (const auto& info : priorityQueue.getTopk()) {
            displayRecord.push_back(cmdType + "," + employeeDB->employeeList[info.getEmployeeNum()].getString());
        }
        return displayRecord;
    }

protected:
    SearchEngine searchEngine;
    EmployeeDB* employeeDB;
    const string EMPLOYEENUM{ "employeeNum" };
    const string BIRTHDAY{ "birthday" };
    const string NAME{ "name" };
    const string CERTI{ "certi" };
    const string CL{ "cl" };
    const string PHONENUM{ "phoneNum" };
    const char CMD_DISC{ ',' };
    const int MOD_TARGET_KEY_IDX = 6; 
    const int MOD_TARGET_VALUE_IDX = 7;
    PriorityQueue priorityQueue;
};

class AddCommand : public ICommand {
public:
    virtual string runCmd(vector<string>& command) override;

private:
    const int ADD_CMD_EMPLOYEENUM_INFO_IDX = 4;
    const int ADD_CMD_NAME_INFO_IDX = 5;
    const int ADD_CMD_LEVEL_INFO_IDX = 6;
    const int ADD_CMD_PHONENUM_INFO_IDX = 7;
    const int ADD_CMD_BIRTHDAY_INFO_IDX = 8;
    const int ADD_CMD_CERTI_INFO_IDX = 9;
};

class DeleteCommand : public ICommand {
public:
    virtual string runCmd(vector<string>& command) override;
};

class ModifyCommand : public ICommand {
public:
    virtual string runCmd(vector<string>& command) override;
};

class SearchCommand : public ICommand {
public:
    virtual string runCmd(vector<string>& command) override;

private:	
	const int SCH_CMD_PRINT_INFO_IDX = 1;

	string convertToString(vector<string> strList) {
		string result;
		for (const auto& str : strList) {
			result += str + "\n";
		}
		return result.substr(0, result.size() - 1);
	}
};