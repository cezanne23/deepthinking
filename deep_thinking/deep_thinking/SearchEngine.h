#pragma once
#include <map>
#include <string>
#include <vector>

#include "SearchPolicy.h"
#include "EmployeeInfo.h"
using namespace std;

class SearchEngine {
 public:
  vector<int> seachID(const map<int, EmployeeInfo> &employeeInfo,
                      const string condition);

 private:
  // EmployeeInfo data_;
  Search *searchPolicy;
#if 0
  vector<int> searchByLastName(string name);
  vector<int> searchByFirstName(string name);
  vector<int> searchByPhoneNumberMid(unsigned int condition);
  vector<int> searchByPhoneNumberLast(unsigned int condition);
  vector<int> searchByBirthYear(unsigned int condition);
  vector<int> searchByBirthMonth(unsigned int condition);
  vector<int> searchByBirthDay(unsigned int condition);
#endif
};
