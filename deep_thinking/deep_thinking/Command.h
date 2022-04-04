#pragma once
#include <iostream>
#include <map>
#include "EmployeeInfo.h"
#include "SearchEngine.h"

using namespace std;

class ICommand {
public:
	virtual string runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) = 0;

protected:
	SearchEngine searchEngine;
};

class AddCommand : public ICommand {
public:
	virtual string runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) override;

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
	virtual string runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) override;
};

class ModifyCommand : public ICommand {
public:
	virtual string runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) override;
};

class SearchCommand : public ICommand {
public:
	virtual string runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) override;
};
