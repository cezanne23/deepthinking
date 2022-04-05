#pragma once

#include <iostream>
#include <sstream>

#include "StringSplitter.h"
using namespace std;

class EmployeeInfo {
public:
    EmployeeInfo() {}

    EmployeeInfo(string employeeNum, string name, string level, string phoneNum, string birthday, string certi)
        : employeeNum_(employeeNum), level_(level), certi_(certi) {
        initName(name);
        initBirthday(birthday);
        initPhoneNum(phoneNum);
    }

    const string getEmployeeNum() const { return employeeNum_; }
    const string getName() const { return firstName_ + " " + lastName_; }
    const string getFirstName() const { return firstName_; }
    const string getLastName() const { return lastName_; }
    const string getLevel() const { return level_; }

    const string getPhoneNum() const {
        if (phoneMidNum_.size() > 0 && phoneLastNum_.size() > 0) {
            return "010-" + phoneMidNum_ + "-" + phoneLastNum_;
        }
        return "";
    }
    const string getPhoneMidNum() const { return phoneMidNum_; }
    const string getPhoneLastNum() const { return phoneLastNum_; }

    const string getBirthDate() const { return birthYear_ + birthMonth_ + birthDay_; }
    const string getBirthYear() const { return birthYear_; }
    const string getBirthMonth() const { return birthMonth_; }
    const string getBirthDay() const { return birthDay_; }
    const string getCerti() const { return certi_; }
    
    // Set
    void setEmployeeNum(string value)  {   employeeNum_ = value; }
    void setName(string value) {
        initName(value);
    }
    void setFirstName(string value)   {   firstName_ = value; }
    void setLastName(string value)   {   lastName_ = value; }
    void setLevel(string value)   {   level_ = value; }

    void setPhoneNum(string value)   {
        initPhoneNum(value);
    }
    void setPhoneMidNum(string value)   {   phoneMidNum_ = value; }
    void setPhoneLastNum(string value)   {   phoneLastNum_ = value; }

    void setBirthDate(string value) {
        initBirthday(value);
    }
    void setBirthYear(string value)   {   birthYear_ = value; }
    void setBirthMonth(string value)   {   birthMonth_ = value; }
    void setBirthDay(string value)   {   birthDay_ = value; }
    void setCerti(string value)   {  certi_ = value; }

    const string getString() const {
        return getEmployeeNum() + "," + getName() + "," + getLevel() + "," + getPhoneNum()
            + "," + getBirthDate() + "," + getCerti();
    }

    bool operator== (const EmployeeInfo& info) const {
        return (employeeNum_ == info.getEmployeeNum()
            && getName() == info.getName()
            && level_ == info.getLevel()
            && getPhoneNum() == info.getPhoneNum()
            && getBirthDate() == info.getBirthDate()
            && certi_ == info.getCerti());
    }

    bool operator!= (const EmployeeInfo& info) const {
        return (employeeNum_ != info.getEmployeeNum()
            || getName() != info.getName()
            || level_ != info.getLevel()
            || getPhoneNum() != info.getPhoneNum()
            || getBirthDate() != info.getBirthDate()
            || certi_ != info.getCerti());
    }

    friend ostream& operator<<(ostream& os, const EmployeeInfo& info) {
        os << "ID(" << info.getEmployeeNum() << ") name (" << info.getName() << ") level(" << info.getLevel()
            << ") " << "phoneNum(" << info.getPhoneNum() << ") birthday(" << info.getBirthDate() << ") certi("
            << info.getCerti() << ") \n";
        return os;
    }

    bool operator < (const EmployeeInfo& info) const {
        if (getULemployeeNum(getEmployeeNum()) < getULemployeeNum(info.getEmployeeNum())) {
            return true;
        }
        return false;
    }

    bool operator > (const EmployeeInfo& info) const {
        if (getULemployeeNum(getEmployeeNum()) > getULemployeeNum(info.getEmployeeNum())) {
            return true;
        }
        return false;
    }
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

    void initPhoneNum(string phoneNum) {
        vector<string> phoneNumList = StringSplitter().splitString(phoneNum, '-');

        if (phoneNumList.size() < 3 || phoneNumList[0] != "010") {
            cout << "invalid phoneNumber format";
            return;
        }
        phoneMidNum_ = phoneNumList[1];
        phoneLastNum_ = phoneNumList[2];
    }
private:
    size_t getULemployeeNum(const string& employeeNum) const {
        const size_t numThreshold = 69000000;
        size_t employeeNum_UL = stoul(employeeNum.c_str());
        if (employeeNum_UL < numThreshold) {
            employeeNum_UL += numThreshold;
        }
        else {
            employeeNum_UL -= numThreshold;
        }
        return employeeNum_UL;
    }

    string employeeNum_;
    string firstName_;
    string lastName_;
    string level_;
    string phoneMidNum_;
    string phoneLastNum_;
    string birthYear_;
    string birthMonth_;
    string birthDay_;
    string certi_;
};

