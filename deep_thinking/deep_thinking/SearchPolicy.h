#pragma once

#include <string>
#include <vector>
#include <map>
#include <functional>
#include "EmployeeInfo.h"

using namespace std;

class Search {
public:
	const int SEARCH_KEY_IDX = 5;
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
		if (parsedCmds[2] == "-m") {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getPhoneNum().substr(4, 4) == key; });
		}
		else if (parsedCmds[2] == "-l") {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getPhoneNum().substr(9, 4) == key; });
		}
	};;
};

class SearhByBirth : public Search {
private:
	virtual vector<string> search(const map<string, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds)  override {
		string key = parsedCmds[SEARCH_KEY_IDX];
		if (parsedCmds[2] == "-d") {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getBirthday().substr(6, 2) == key; });
		}
		else if (parsedCmds[2] == "-m") {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getBirthday().substr(4, 2) == key; });
		}
		else if (parsedCmds[2] == "-y") {
			return search_base(employeeInfo, [&key](const EmployeeInfo& employA)  -> bool {
				return employA.getBirthday().substr(0, 4) == key; });
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