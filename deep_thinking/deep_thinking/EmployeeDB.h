#pragma once
#include <iostream>
#include <map>
#include "EmployeeInfo.h"

using namespace std;

class EmployeeDB {
public:
    static EmployeeDB& getDB() {
        static EmployeeDB* instance = new EmployeeDB();

        return *instance;
    }

    map<string, EmployeeInfo> employeeList;
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

private:
    EmployeeDB() {};
};
