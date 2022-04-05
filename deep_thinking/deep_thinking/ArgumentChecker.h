#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ArgumentChecker {
public:
    ArgumentChecker(const string& command) : argument_name_(command) {}
    virtual bool check(const string& argument) const = 0;
    const string& getArgumentName() {
        return argument_name_;
    }
protected:
    string argument_name_;
};

class EmployNumChecker : public ArgumentChecker {
public:
    EmployNumChecker() : ArgumentChecker("employeeNum") {}
    virtual bool check(const string& argument) const override {
        size_t employ_number = stol(argument);
        if ((0 <= employ_number && employ_number < 22000000UL) || 69000000UL <= employ_number && employ_number < 100000000UL) {
            return true;
        }
        return false;
    }
};

class NameChecker : public ArgumentChecker {
public:
    NameChecker() : ArgumentChecker("name") {}
    virtual bool check(const string& argument) const override {
        if (argument.size() > max_name_length_) return false;
        for (auto& c : argument) {
            if (c != ' ' && islower(c)) return false;
        }
        return true;
    }
private:
    const size_t max_name_length_ = 15;
};

class CareerLevelChecker : public ArgumentChecker {
public:
    CareerLevelChecker() : ArgumentChecker("cl") {}
    virtual bool check(const string& argument) const override {
        for (auto& cl : career_levels_) {
            if (argument == cl) {
                return true;
            }
        }
        return false;
    }
private:
    const vector<string> career_levels_ = { "CL1", "CL2", "CL3", "CL4" };
};

class BirthdayChecker : public ArgumentChecker {
public:
    BirthdayChecker() : ArgumentChecker("birthday") {}
    virtual bool check(const string& argument) const override {
        return argument.size() > max_birthday_length_ ? false : true;
    }
private:
    const size_t max_birthday_length_ = 8;
};

class PhoneNumberChecker : public ArgumentChecker {
public:
    PhoneNumberChecker() : ArgumentChecker("phoneNum") {}
    virtual bool check(const string& argument) const override {
        if (argument.substr(0, 3) != phone_number_prefix_) {
            return false;
        }
        size_t dash_count = count(argument.begin(), argument.end(), '-');
        return (dash_count == 2) ? true : false;
    }
private:
    const string phone_number_prefix_ = "010";
};

class SwCertiChecker : public ArgumentChecker {
public:
    SwCertiChecker() : ArgumentChecker("certi") {}
    virtual bool check(const string& argument) const override {
        for (auto& certi : certifications_) {
            if (argument == certi) {
                return true;
            }
        }
        return false;
    }
private:
    const vector<string> certifications_ = { "ADV", "PRO", "EX" };
};