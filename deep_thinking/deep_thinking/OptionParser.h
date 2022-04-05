#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class OptionType {
    NONE,
    DATE,
    YEAR,
    MONTH,
    DAY,
    FULL_NAME,
    FIRST_NAME,
    LAST_NAME,
    PHONE_NUM,
    MID_PHONE_NUM,
    LAST_PHONE_NUM,
    EMPLOYEE_NUM,
    CERTI,
    LEVEL,
    INVALID
};

class OptionParser {
public:
    bool hasPrintOption(const vector<string>& commands) {
        return commands[OPTION1_IDX] == "-p" ? true : false;
    }

    OptionType getOptionType(const vector<string>& commands)
    {
        if (commands[COMMAND_IDX] == "ADD") {
            return OptionType::NONE;
        }

        string option = getMatchedOption(commands[OPTION2_IDX]);
        if (option == NOT_MATCHED) {
            throw invalid_argument("Invalid Option");
        }

        string key = commands[OPTION_KEY_IDX];
        if (key == NAME) {
            return getNameOption(option);
        }
        else if (key == EMPLOYEENUM) {
            return OptionType::EMPLOYEE_NUM;
        }
        else if (key == BIRTHDAY) {
            return getBirthdayOption(option);
        }
        else if (key == PHONENUM) {
            return getPhoneNumOption(option);
        }
        else if (key == CERTI) {
            return OptionType::CERTI;
        }
        else if (key == CL) {
            return OptionType::LEVEL;
        }
        throw invalid_argument("Invalid Column(key)");
    }

private:
    const string NO_OPT = " ";
    const string NOT_MATCHED = "NOT_MATCHED";
    const vector<string> validOptionList = { "-f", "-l", "-m", "-y", "-d", NO_OPT };
    const int COMMAND_IDX = 0;
    const int OPTION1_IDX = 1;
    const int OPTION2_IDX = 2;
    const int OPTION3_IDX = 3;
    const int OPTION_KEY_IDX = 4;
    const string EMPLOYEENUM{ "employeeNum" };
    const string BIRTHDAY{ "birthday" };
    const string NAME{ "name" };
    const string CERTI{ "certi" };
    const string CL{ "cl" };
    const string PHONENUM{ "phoneNum" };

    string getMatchedOption(const string& option) {
        for (auto& v : validOptionList) {
            if (v == option) return v;
        }
        return NOT_MATCHED;
    }

    OptionType getNameOption(const string& option)
    {
        if (option == "-f") {
            return OptionType::FIRST_NAME;
        }
        if (option == "-l") {
            return OptionType::LAST_NAME;
        }
        return OptionType::FULL_NAME;
    }

    OptionType getPhoneNumOption(const string& option)
    {
        if (option == "-m") {
            return OptionType::MID_PHONE_NUM;
        }
        if (option == "-l") {
            return OptionType::LAST_PHONE_NUM;
        }
        return OptionType::PHONE_NUM;
    }

    OptionType getBirthdayOption(const string& option)
    {
        if (option == "-y") {
            return OptionType::YEAR;
        }
        if (option == "-m") {
            return OptionType::MONTH;
        }
        if (option == "-d") {
            return OptionType::DAY;
        }
        return OptionType::DATE;
    }
};
