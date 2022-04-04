#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CommandParser {
public:
	CommandParser() {
		arguments_.clear();
		arguments_.reserve(max_num_argument_);
	}

	const vector<string>& parseCommand(string command);
	bool validateArguments(const vector<string>& arguments);

private:
	const int max_num_argument_ = 16;
	const char separator_ = ',';
	const char empty = ' ';
	vector<string> arguments_;
};