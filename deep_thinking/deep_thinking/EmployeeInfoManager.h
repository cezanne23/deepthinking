#pragma once
#include <iostream>
#include <map>

#include "Command.h"
using namespace std;

class EmployeeInfoManager {
 public:
  string ExcuteCommand(string singleCmdString);

 private:
  // CommandPaser commandPaser;
  map<int, EmployeeInfo> employeeList;
};
