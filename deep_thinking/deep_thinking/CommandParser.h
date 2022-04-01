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
	void splitCommand(const string& command, const string separator);

private:
	const int max_num_argument_ = 16;
	const string separator_ = ",";
	const string empty = " ";
	vector<string> arguments_;
};