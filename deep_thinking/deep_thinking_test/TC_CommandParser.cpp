#include "pch.h"
#include "TC_CommandParser.h"

TEST_F(FixtureCommandGenerator, ValidArgumentTest) {

	CommandParser command_parser{};

	for (auto& command : validCommands_) {
		vector<string> argument = command_parser.parseCommand(command);
		EXPECT_TRUE(command_parser.validateArguments(argument));
	}
}

TEST(CommandParserTest, InvalidArugmentTest) {

	CommandParser command_parser{};

	vector<string> invalid_command_samples = {
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

	for (auto& command : invalid_command_samples) {
		vector<string> argument = command_parser.parseCommand(command);
		EXPECT_FALSE(command_parser.validateArguments(argument));
	}
}