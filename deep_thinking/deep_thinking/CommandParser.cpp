#include "CommandParser.h"
#include "ArgumentChecker.h"

void CommandParser::splitCommand(const string& command, const string separator) {
	size_t sPos = 0;
	size_t ePos = command.find(separator);
	string subString{};

	ePos = command.find(separator, sPos);

	while (ePos != string::npos) {
		subString = command.substr(sPos, ePos - sPos);
		arguments_.emplace_back(subString);
		sPos = ePos + 1;
		ePos = command.find(separator, sPos);
	}
}


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
				cout << "[DEBUG] failed on validateAddCommand : " << checker->get_argument_name() << endl;
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
	splitCommand(command + separator_, separator_);
	return arguments_;
}