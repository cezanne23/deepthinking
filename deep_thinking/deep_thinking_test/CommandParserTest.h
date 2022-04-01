#pragma once

#include "../deep_thinking/CommandParser.cpp"
#include "../deep_thinking/ArgumentChecker.h"
#include "pch.h"

#include <fstream>

using namespace std;

class FixtureCommandGenerator : public ::testing::Test {
protected:
	void SetUp() override {

		initialize();

		ifstream fin{};
		fin.open("input_20_20.txt");
		if (!fin.fail()) {
			for (string command; getline(fin, command);) {
				validCommands_.emplace_back(command);
			}
			fin.close();
		}

		invalidCommands_ = {
			// Invalid EmployNum
			"ADD, , , ,68999999,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV",
			"ADD, , , ,100000000,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV",
			"ADD, , , ,22000000,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV",
			// Invalid Name
			"ADD, , , ,99999999,VXIHXOTH jhop,CL3,010-3112-2609,19771211,ADV",
			"ADD, , , ,99999999,VXIHXOTH JHOPBTS,CL3,010-3112-2609,19771211,ADV",
			// Invalid CL
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL0,010-3112-2609,19771211,ADV",
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL8,010-3112-2609,19771211,ADV",
			// Invalid PhoneNumber
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,011-3112-2609,19771211,ADV",
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,016-3112-2609,19771211,ADV",
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112--2609,19771211,ADV"
			// Invalid Birthday
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,197712121,ADV",
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,1977123211,ADV",
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,424771211,ADV"
			// Invalid Certi
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771212,IMM",
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771212,BEST",
			"ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771212,GOD"
		};
	}

	void TearDown() override {
		validCommands_.clear();
		invalidCommands_.clear();
	}

	void initialize() {
		validCommands_.clear();
		invalidCommands_.clear();
	}

public:
	vector<string> validCommands_;
	vector<string> invalidCommands_;
};