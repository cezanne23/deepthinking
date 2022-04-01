#pragma once

#include "../deep_thinking/CommandParser.h"
#include "../deep_thinking/ArgumentChecker.h"
#include "pch.h"

#include <fstream>

using namespace std;

class FixtureCommandGenerator : public ::testing::Test {
protected:
	void SetUp() override {

		initialize();

		ifstream fin{};
		fin.open("./testvector/input_20_20.txt");
		if (!fin.fail()) {
			for (string command; getline(fin, command);) {
				validCommands_.emplace_back(command);
			}
			fin.close();
		}
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