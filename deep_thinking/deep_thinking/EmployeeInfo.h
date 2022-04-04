#pragma once

#include <iostream>
#include <sstream>
using namespace std;

class EmployeeInfo {
public:
    EmployeeInfo() {}

    EmployeeInfo(string employeeNum, string name, string level, string phoneNum, string birthday, string certi)
        : employeeNum_(employeeNum), level_(level), phoneNum_(phoneNum), certi_(certi) {
        initName(name);
        initBirthday(birthday);    
    }

    const string getEmployeeNum() const { return employeeNum_; }
    const string getName() const { return firstName_ + " "  + lastName_; }
    const string getFirstName() const { return firstName_; }
    const string getLastName() const { return lastName_; }
    const string getLevel() const { return level_; }
    const string getPhoneNum() const { return phoneNum_; }
    const string getBirthDate() const { return birthYear_ + birthMonth_ + birthDay_; }
    const string getBirthYear() const { return birthYear_ ; }
    const string getBirthMonth() const { return birthMonth_; }
    const string getBirthDay() const { return birthDay_; }
    const string getCerti() const { return certi_; }

    bool operator== (const EmployeeInfo& info) const {
        return (employeeNum_ == info.getEmployeeNum()
            && getName() == info.getName()
            && level_ == info.getLevel()
            && phoneNum_ == info.getPhoneNum()
            && getBirthDate() == info.getBirthDate()
            && certi_ == info.getCerti());
    }

    bool operator!= (const EmployeeInfo& info) const {
        return (employeeNum_ != info.getEmployeeNum()
            || getName() != info.getName()
            || level_ != info.getLevel()
            || phoneNum_ != info.getPhoneNum()
            || getBirthDate() != info.getBirthDate()
            || certi_ != info.getCerti());
    }

    friend ostream& operator<<(ostream& os, const EmployeeInfo& info) {
        os << "ID(" << info.getEmployeeNum() << ") name (" << info.getName() << ") level(" << info.getLevel()
            << ") " << "phoneNum(" << info.getPhoneNum() << ") birthday(" << info.getBirthDate() << ") certi("
            << info.getCerti() << ") \n";
        return os;
    }

private:
    void initName(string name) {
        istringstream iss(name);
        iss >> firstName_ >> lastName_;
    }

    void initBirthday(string day) {
        if (day.size() < string("yyyymmdd").size()) {
            cout << "invalid date format";
            return;
        }

        birthYear_ = day.substr(0, 4);
        birthMonth_ = day.substr(4, 2);
        birthDay_ = day.substr(6, 2);
    }

    string employeeNum_;
    string firstName_;
    string lastName_;
    string level_;
    string phoneNum_;
    string birthYear_;
    string birthMonth_;
    string birthDay_;
    string certi_;
};

