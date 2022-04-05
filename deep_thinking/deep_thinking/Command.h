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

    vector<string> displayEmployeeInfo(const vector<string>& list, const string cmdType) {
        vector<string> displayRecord;
        PriorityQueue priorityQueue;

        for (const auto& employeeNum : priorityQueue.sort_partial(list, 5)) {
            displayRecord.push_back(cmdType + "," + employeeDB->employeeList[employeeNum].getString());
        }

        return displayRecord;
    }
    const string EMPLOYEENUM{ "employeeNum" };
    const string BIRTHDAY{ "birthday" };
    const string NAME{ "name" };
    const string CERTI{ "certi" };
    const string CL{ "cl" };
    const string PHONENUM{ "phoneNum" };
    const char CMD_DISC{ ',' };
    const int MOD_TARGET_KEY_IDX = 6;
    const int MOD_TARGET_VALUE_IDX = 7;


protected:
    SearchEngine searchEngine;
    EmployeeDB* employeeDB;
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

class MODUpdate {
public:
    virtual void update(EmployeeInfo& enployeeInfo, string value) = 0;
};

class MODUpdateName : public MODUpdate {
    virtual void update(EmployeeInfo& enployeeInfo, string value) override { enployeeInfo.setName(value); }
};

class MODUpdateLevel : public MODUpdate {
    virtual void update(EmployeeInfo& enployeeInfo, string value) override { enployeeInfo.setLevel(value); }
};

class MODUpdatePhoneNum : public MODUpdate {
    virtual void update(EmployeeInfo& enployeeInfo, string value) override { enployeeInfo.setPhoneNum(value); }
};

class MODUpdateBirth : public MODUpdate {
    virtual void update(EmployeeInfo& enployeeInfo, string value) override { enployeeInfo.setBirthDate(value); }
};

class MODUpdateCerti : public MODUpdate {
    virtual void update(EmployeeInfo& enployeeInfo, string value) override { enployeeInfo.setCerti(value); }
};

class MODUpdateEmployeeNum : public MODUpdate {
    virtual void update(EmployeeInfo& enployeeInfo, string value) override { /* no nothing*/ }
};

class ModifyCommand : public ICommand {
public:
    ModifyCommand() {
        updateList.insert({ NAME , new MODUpdateName });
        updateList.insert({ CL , new MODUpdateLevel });
        updateList.insert({ PHONENUM , new MODUpdatePhoneNum });
        updateList.insert({ BIRTHDAY , new MODUpdateBirth });
        updateList.insert({ CERTI , new MODUpdateCerti });
        updateList.insert({ EMPLOYEENUM , new MODUpdateEmployeeNum });
    };
    virtual string runCmd(vector<string>& command) override;
private:
    map<string, MODUpdate*> updateList;
};

class SearchCommand : public ICommand {
public:
    virtual string runCmd(vector<string>& command) override;
};