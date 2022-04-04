#include "pch.h"
#include "CommandParserTest.h"

TEST_F(FixtureCommandGenerator, ValidArgumentTest) {
	CommandParser command_parser{};

	for (auto& command : validCommands_) {
		vector<string> argument = command_parser.parseCommand(command);
		EXPECT_TRUE(command_parser.validateArguments(argument));
	}
}

TEST_F(FixtureCommandGenerator, InvalidArugmentTest){
	CommandParser command_parser{};

	for (auto& command : invalidCommands_) {
		vector<string> argument = command_parser.parseCommand(command);
		EXPECT_FALSE(command_parser.validateArguments(argument));
	}
}