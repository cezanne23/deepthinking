#include "Command.h"

using namespace std;

string AddCommmand::runCmd(map<int, EmployeeInfo>, string command) {
  return "";
};

string DeleteCommmand::runCmd(map<int, EmployeeInfo>, string command) {
  return "DeleteCommand";
};

string ModifyCommmand::runCmd(map<int, EmployeeInfo>, string command) {
  return "ModifyCommand";
};

string SearchCommmand::runCmd(map<int, EmployeeInfo>, string command) {
  return "SearchCommand";
};
