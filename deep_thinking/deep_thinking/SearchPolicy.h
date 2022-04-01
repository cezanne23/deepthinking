#pragma once

#include <string>
#include <vector>
#include <map>
#include "Employee.h"

using namespace std;

class Search {
public:
	virtual vector<int> search(const map<int, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds) const = 0;
};

class SearhById : public Search {
private:
	virtual vector<int> search(const map<int, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds) const override {
		vector<int> result;
		result.push_back(590);
		return result;
	};
};

class SearhByName : public Search {
private:
	virtual vector<int> search(const map<int, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds) const override {
		vector<int> result;
		result.push_back(591);

		return result;
	};
};

class SearhByPhoneNumber : public Search {
private:
	virtual vector<int> search(const map<int, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds) const override {
		vector<int> result;
		result.push_back(592);

		return result;
	};
};

class SearhByBirth : public Search {
private:
	virtual vector<int> search(const map<int, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds) const override {
		vector<int> result;
		result.push_back(593);

		return result;
	};
};

class SearhByCerti : public Search {
private:
	virtual vector<int> search(const map<int, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds) const override {
		vector<int> result;
		result.push_back(594);

		return result;
	};
};

class SearhByCL : public Search {
private:
	virtual vector<int> search(const map<int, EmployeeInfo>& employeeInfo, const vector<string>& parsedCmds) const override {
		vector<int> result;
		result.push_back(595);

		return result;
	};
};