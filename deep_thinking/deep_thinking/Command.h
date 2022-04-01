#pragma once
#include <iostream>
#include <map>
#include "Employee.h"

using namespace std;

class ICommand {
 public:
  virtual string runCmd(map<int, EmployeeInfo>, string command) = 0;
};

class AddCommmand : public ICommand {
 public:
  virtual string runCmd(map<int, EmployeeInfo>, string command) override;
};

class DeleteCommmand : public ICommand {
 public:
  virtual string runCmd(map<int, EmployeeInfo>, string command) override;
};

class ModifyCommmand : public ICommand {
 public:
  virtual string runCmd(map<int, EmployeeInfo>, string command) override;
};

class SearchCommmand : public ICommand {
 public:
  virtual string runCmd(map<int, EmployeeInfo>, string command) override;
};
