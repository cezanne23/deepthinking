#pragma once
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include "SearchPolicy.h"

using namespace std;

class InputParcer {
public:
	vector<string> split(string str, char disc) {
		vector<string> result;
		stringstream ss(str);
		string word;

		while (getline(ss, word, disc)) { // ',')) {
			while (' ' == word[0])  word.erase(0, 1);
			result.push_back(word);
		}
#ifdef NOTDF
		ColumnChecker checker;
		if (checker.columnCheck(result) == false) {
			result.clear();
		}
#endif
		return result;
	}
private:
};

class SearchEngineCore {
public:
	SearchEngineCore() {
		searchPolicyList.insert({ EMPLOYEENUM, new SearhById() });
		searchPolicyList.insert({ NAME, new SearhByName() });
		searchPolicyList.insert({ BIRTHDAY, new SearhByBirth() });
		searchPolicyList.insert({ CERTI, new SearhByCerti() });
		searchPolicyList.insert({ CL, new SearhByCL() });
		searchPolicyList.insert({ PHONENUM, new SearhByPhoneNumber() });

	};
	vector<string> seachID(const map<string, EmployeeInfo>& employeeInfo,
		const vector<string>& parsedCmds);

	template <typename T1>
	vector<EmployeeInfo> search(const T1 database, const int condition);

private:
	map<string, Search*> searchPolicyList;
	InputParcer parSer;
	const string EMPLOYEENUM{ "employeeNum" };
	const string BIRTHDAY{ "birthday" };
	const string NAME{ "name" };
	const string CERTI{ "certi" };
	const string CL{ "cl" };
	const string PHONENUM{ "phoneNum" };
	const char CMD_DISC{ ',' };
	const int SEARCH_OPTION_IDX = 4;
};

class SearchEngine { // Interface class
public:
	SearchEngine() { employDB = &EmployeeDB::getDB(); };
	vector<string> seachID(const map<string, EmployeeInfo>& employeeInfo,
		const vector<string>& parsedCmds) {
		return internalEngine.seachID(employeeInfo, parsedCmds);
	};
	vector<string> seachID(const vector<string>& parsedCmds) {
		return internalEngine.seachID(employDB->employeeList, parsedCmds);
	};
	vector<EmployeeInfo*> seachEmployee(const map<string, EmployeeInfo>& employeeInfo,
		const vector<string>& parsedCmds);
	vector<EmployeeInfo*> seachEmployee(const vector<string>& parsedCmds);
private:
	SearchEngineCore internalEngine;
	EmployeeDB* employDB;
};


