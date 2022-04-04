#pragma once

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class StringSplitter {
public:
	static vector<string> splitString(const string& str, const char separator) {
		istringstream iss(str);
		string buf;
		vector<string> splitted_result{};

		while (getline(iss, buf, separator)) {
			splitted_result.push_back(buf);
		}

		return splitted_result;
	}
};
