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

class MODUpdate { 
public:
    MODUpdate(EmployeeDB* employeeDB) : employeeDB_(employeeDB) {}
    virtual void update( EmployeeInfo& employeeInfo, string value)  = 0;

    void modifyOp(multimap<string, string>& map, pair<string, string> old, pair<string, string> update)
    {
        for (auto iter = map.lower_bound(old.first); iter != map.upper_bound(old.first); ++iter) {
            if (old.second == iter->second) {
                map.erase(iter);
                map.insert(update);
                return;
            }
        }
    }

    EmployeeDB* getDB() {
        if (nullptr == employeeDB_) {
            throw invalid_argument("employeeDB_ is empty");
        }
        return employeeDB_;
    }
private:
    EmployeeDB* employeeDB_ = nullptr;
};

class MODUpdateName : public MODUpdate {
public:
    MODUpdateName(EmployeeDB* employeeDB) : MODUpdate(employeeDB) {}
    virtual void update(EmployeeInfo& employeeInfo, string value) override {
        string fullName = value;
        vector<string> splittedName = StringSplitter::splitString(fullName, ' ');
        string firstName = splittedName[0];
        string lastName = splittedName[1];

        modifyOp(getDB()->fullNameMap, pair<string, string>(employeeInfo.getName(), employeeInfo.getEmployeeNum()), pair<string, string>(fullName, employeeInfo.getEmployeeNum()));
        modifyOp(getDB()->firstNameMap, pair<string, string>(employeeInfo.getFirstName(), employeeInfo.getEmployeeNum()), pair<string, string>(firstName, employeeInfo.getEmployeeNum()));
        modifyOp(getDB()->lastNameMap, pair<string, string>(employeeInfo.getLastName(), employeeInfo.getEmployeeNum()), pair<string, string>(lastName, employeeInfo.getEmployeeNum()));

        employeeInfo.setName(value);
    }
};

class MODUpdateLevel : public MODUpdate {
public:
    MODUpdateLevel(EmployeeDB* employeeDB) : MODUpdate(employeeDB) {}
    virtual void update(EmployeeInfo& employeeInfo, string value) override {
        modifyOp(getDB()->levelMap, pair<string, string>(employeeInfo.getLevel(), employeeInfo.getEmployeeNum()), pair<string, string>(value, employeeInfo.getEmployeeNum()));
        employeeInfo.setLevel(value); 
    }
};

class MODUpdatePhoneNum : public MODUpdate {
public:
    MODUpdatePhoneNum(EmployeeDB* employeeDB) : MODUpdate(employeeDB) {}
    virtual void update(EmployeeInfo& employeeInfo, string value) override { 
        string phoneNum = value;
        vector<string> splittedPhoneNum = StringSplitter::splitString(phoneNum, '-');
        string midPhoneNum = splittedPhoneNum[1];
        string lastPhoneNum = splittedPhoneNum[2];

        modifyOp(getDB()->phoneNumMap, pair<string, string>(employeeInfo.getPhoneNum(), employeeInfo.getEmployeeNum()), pair<string, string>(phoneNum, employeeInfo.getEmployeeNum()));
        modifyOp(getDB()->phoneMidNumMap, pair<string, string>(employeeInfo.getPhoneMidNum(), employeeInfo.getEmployeeNum()), pair<string, string>(midPhoneNum, employeeInfo.getEmployeeNum()));
        modifyOp(getDB()->phoneLastNumMap, pair<string, string>(employeeInfo.getPhoneLastNum(), employeeInfo.getEmployeeNum()), pair<string, string>(lastPhoneNum, employeeInfo.getEmployeeNum()));

        employeeInfo.setPhoneNum(value); 
    }
};

class MODUpdateBirth : public MODUpdate {
public:
    MODUpdateBirth(EmployeeDB* employeeDB) : MODUpdate(employeeDB) {}
    virtual void update(EmployeeInfo& employeeInfo, string value) override {
        string date = value;
        string year = date.substr(0, 4);
        string month = date.substr(4, 2);
        string day = date.substr(6, 2);

        modifyOp(getDB()->birthDateMap, pair<string, string>(employeeInfo.getBirthDate(), employeeInfo.getEmployeeNum()), pair<string, string>(date, employeeInfo.getEmployeeNum()));
        modifyOp(getDB()->birthYearMap, pair<string, string>(employeeInfo.getBirthYear(), employeeInfo.getEmployeeNum()), pair<string, string>(year, employeeInfo.getEmployeeNum()));
        modifyOp(getDB()->birthMonthMap, pair<string, string>(employeeInfo.getBirthMonth(), employeeInfo.getEmployeeNum()), pair<string, string>(month, employeeInfo.getEmployeeNum()));
        modifyOp(getDB()->birthDayMap, pair<string, string>(employeeInfo.getBirthDay(), employeeInfo.getEmployeeNum()), pair<string, string>(day, employeeInfo.getEmployeeNum()));

        employeeInfo.setBirthDate(value);
    }
};

class MODUpdateCerti : public MODUpdate {
public:
    MODUpdateCerti(EmployeeDB* employeeDB) : MODUpdate(employeeDB) {}
    virtual void update(EmployeeInfo& employeeInfo, string value) override {
        modifyOp(getDB()->certiMap, pair<string, string>(employeeInfo.getCerti(), employeeInfo.getEmployeeNum()), pair<string, string>(value, employeeInfo.getEmployeeNum()));
        employeeInfo.setCerti(value);
    }
};

class MODUpdateEmployeeNum : public MODUpdate {
public:
    MODUpdateEmployeeNum(EmployeeDB* employeeDB) : MODUpdate(employeeDB) {}
    virtual void update(EmployeeInfo& enployeeInfo, string value) override { /* no nothing*/ }
};

class ModifyCommand : public ICommand {
public:
    ModifyCommand() { 
        updateList.insert({ NAME , new MODUpdateName(employeeDB)});
        updateList.insert({ CL , new MODUpdateLevel(employeeDB) });
        updateList.insert({ PHONENUM , new MODUpdatePhoneNum(employeeDB) });
        updateList.insert({ BIRTHDAY , new MODUpdateBirth(employeeDB) });
        updateList.insert({ CERTI , new MODUpdateCerti(employeeDB) });
        updateList.insert({ EMPLOYEENUM , new MODUpdateEmployeeNum(employeeDB) });
    };
    virtual string runCmd(vector<string>& command) override;
private:
    map<string, MODUpdate*> updateList;
};

class SearchCommand : public ICommand {
public:
    virtual string runCmd(vector<string>& command) override;
};