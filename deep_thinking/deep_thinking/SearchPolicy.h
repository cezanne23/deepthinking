#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "EmployeeDB.h"
#include "EmployeeInfo.h"

using namespace std;

class Search {
public:
	const int SEARCH_KEY_IDX = 5;
	const int SEARCH_OPTION_KEY_IDX = 2;
	const string SEARCH_BIRTH_DAY_STR{ "-d" };
	const string SEARCH_BIRTH_MONTH_STR{ "-m" };
	const string SEARCH_BIRTH_YEAR_STR{ "-y" };
	const string SEARCH_PHONENUMBER_MID_STR{ "-m" };
	const string SEARCH_PHONENUMBER_LAST_STR{ "-l" };


	vector<string> search_base(const map<string, EmployeeInfo>& employeeDict , function<bool (EmployeeInfo)> isMatched) {
		vector<string> result;

		for (auto it = employeeDict.begin(); it != employeeDict.end(); ++it) {
			EmployeeInfo eInfo  = it->second;
			bool res = isMatched(eInfo);
			if (res) {
				result.push_back(it->first);
			}
		}

		return result;
	}
	virtual vector<string> search(const map<string, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds)  = 0;
};

class SearhById : public Search {
private:
	virtual vector<string> search(const map<string, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds)  override {
		string key = parsedCmds[SEARCH_KEY_IDX];
		auto isMatched = [&key](const EmployeeInfo & employA)  -> bool { 
			return employA.getEmployeeNum()  == key; };
		return search_base(employeeInfo, isMatched);
	}; 
};

class SearhByName : public Search {
private:
	virtual vector<string> search(const map<string, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds)  override {
		string key = parsedCmds[SEARCH_KEY_IDX];
		auto isMatched = [&key](const EmployeeInfo& employA)  -> bool {
			return employA.getName() == key; };
		return search_base(employeeInfo, isMatched);
	};
};

class SearhByPhoneNumber : public Search {
private:
	virtual vector<string> search(const map<string, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds)  override {
		string key = parsedCmds[SEARCH_KEY_IDX];
		if (parsedCmds[SEARCH_OPTION_KEY_IDX] == SEARCH_PHONENUMBER_MID_STR) {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getPhoneNum().substr(4, 4) == key; });
		}
		else if (parsedCmds[SEARCH_OPTION_KEY_IDX] == SEARCH_PHONENUMBER_LAST_STR) {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getPhoneNum().substr(9, 4) == key; });
		}
	};;
};

class SearhByBirth : public Search {
private:
	virtual vector<string> search(const map<string, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds)  override {
		string key = parsedCmds[SEARCH_KEY_IDX];
		if (parsedCmds[SEARCH_OPTION_KEY_IDX] == SEARCH_BIRTH_DAY_STR) {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getBirthDay() == key; });
		}
		else if (parsedCmds[SEARCH_OPTION_KEY_IDX] == SEARCH_BIRTH_MONTH_STR) {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getBirthMonth() == key; });
		}
		else if (parsedCmds[SEARCH_OPTION_KEY_IDX] == SEARCH_BIRTH_YEAR_STR) {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getBirthYear() == key; });
		}
	};
};

class SearhByCerti : public Search {
private:
	virtual vector<string> search(const map<string, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds)  override {
		string key = parsedCmds[SEARCH_KEY_IDX];
		return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
			return employA.getCerti() == key; });
	};
};

class SearhByCL : public Search {
private:
	virtual vector<string> search(const map<string, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds)  override {
		string key = parsedCmds[SEARCH_KEY_IDX];
		return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
			return employA.getLevel() == key; });
	};
};