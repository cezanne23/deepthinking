#include "CommandParser.h"
#include "ArgumentChecker.h"
#include "StringSplitter.h"

bool CommandParser::validateArguments(const vector<string>& arguments) {
    string command = arguments[0];
    auto isSupportedCommand = [](const string& command)->bool {
        if (command == "ADD" || command == "DEL" || command == "SCH" || command == "MOD") {
            return true;
        }
        return false;
    };

    if (!isSupportedCommand(command)) {
        return false;
    }

    EmployNumChecker employNumChecker{};
    NameChecker nameChecker{};
    CareerLevelChecker clChecker{};
    PhoneNumberChecker phoneNumChecker{};
    BirthdayChecker birthdayChecker{};
    SwCertiChecker certiChecker{};

    if (command == "ADD") {
        size_t argument_index = 4;
        vector<ArgumentChecker*> checkers = { &employNumChecker,
                                              &nameChecker,
                                              &clChecker,
                                              &phoneNumChecker,
                                              &birthdayChecker,
                                              &certiChecker };

        for (auto& checker : checkers) {
            if (checker && checker->check(arguments[argument_index++])) {
                continue;
            }
            else {
                cout << "[DEBUG] failed on validateAddCommand : " << checker->getArgumentName() << endl;
                return false;
            }
        }
    }
    // TODO:
    // SCH, MOD, DEL 에 대한 validate 체크 구현 필요
    return true;
}

const vector<string>& CommandParser::parseCommand(string command) {
    arguments_.clear();
    arguments_ = StringSplitter().splitString(command, separator_);
    return arguments_;
}