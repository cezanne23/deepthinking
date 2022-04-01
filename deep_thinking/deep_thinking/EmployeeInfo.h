#pragma once

#include <iostream>
using namespace std;

class EmployeeInfo {
public:
    EmployeeInfo() {}

    EmployeeInfo(string employeeNum, string name, string level, string phoneNum, string birthday, string certi)
        : employeeNum_(employeeNum), name_(name), level_(level), phoneNum_(phoneNum), birthday_(birthday), certi_(certi) {}

    const string getEmployeeNum() const { return employeeNum_; }
    const string getName() const { return name_; }
    const string getLevel() const { return level_; }
    const string getPhoneNum() const { return phoneNum_; }
    const string getBirthday() const { return birthday_; }
    const string getCerti() const { return certi_; }

    bool operator== (const EmployeeInfo& info) const {
        return (employeeNum_ == info.getEmployeeNum()
            && name_ == info.getName()
            && level_ == info.getLevel()
            && phoneNum_ == info.getPhoneNum()
            && birthday_ == info.getBirthday()
            && certi_ == info.getCerti());
    }

    bool operator!= (const EmployeeInfo& info) const {
        return (employeeNum_ != info.getEmployeeNum()
            || name_ != info.getName()
            || level_ != info.getLevel()
            || phoneNum_ != info.getPhoneNum()
            || birthday_ != info.getBirthday()
            || certi_ != info.getCerti());
    }

    friend ostream& operator<<(ostream& os, const EmployeeInfo& info) {
        os << "ID(" << info.getEmployeeNum() << ") name (" << info.getName() << ") level(" << info.getLevel()
            << ") " << "phoneNum(" << info.getPhoneNum() << ") birthday(" << info.getBirthday() << ") certi("
            << info.getCerti() << ") \n";
        return os;
    }

private:
    string employeeNum_;
    string name_;
    string level_;
    string phoneNum_;
    string birthday_;
    string certi_;
};
