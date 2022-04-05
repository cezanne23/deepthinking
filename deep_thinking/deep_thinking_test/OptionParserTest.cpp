#include "../deep_thinking/OptionParser.h"
#include "../deep_thinking/CommandParser.h"
#include "pch.h"

TEST(OptionParserTest, checkNameOptionType)
{
	vector<string> command;
	CommandParser commandParser{};
	OptionParser optionParser{};

	command = commandParser.parseCommand("ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO");
	EXPECT_EQ(OptionType::NONE, optionParser.getOptionType(command));

	command = commandParser.parseCommand("SCH, , , ,name,AAAA BBBB");
	EXPECT_EQ(OptionType::FULL_NAME, optionParser.getOptionType(command));

	command = commandParser.parseCommand("SCH,-p, , ,name,KYUMOK KIM");
	EXPECT_EQ(OptionType::FULL_NAME, optionParser.getOptionType(command));
	EXPECT_TRUE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("SCH,-p,-k, ,name,KYUMOK KIM");
	EXPECT_THROW(optionParser.getOptionType(command), invalid_argument);

	command = commandParser.parseCommand("SCH,-p,-l, ,name,KYUMOK KIM");
	EXPECT_EQ(OptionType::LAST_NAME, optionParser.getOptionType(command));

	command = commandParser.parseCommand("SCH,-p,-f, ,name,KYUMOK KIM");
	EXPECT_EQ(OptionType::FIRST_NAME, optionParser.getOptionType(command));
}

TEST(OptionParserTest, checkBirthdayOptionType)
{
	vector<string> command;
	CommandParser commandParser{};
	OptionParser optionParser{};

	command = commandParser.parseCommand("DEL, ,-d, ,birthday,19900123");
	EXPECT_EQ(OptionType::DAY, optionParser.getOptionType(command));
	EXPECT_FALSE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("DEL, ,-y, ,birthday,19900123");
	EXPECT_EQ(OptionType::YEAR, optionParser.getOptionType(command));
	EXPECT_FALSE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("DEL,-p,-m, ,birthday,19900123");
	EXPECT_EQ(OptionType::MONTH, optionParser.getOptionType(command));
	EXPECT_TRUE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("DEL,-p, , ,birthday,19900123");
	EXPECT_EQ(OptionType::DATE, optionParser.getOptionType(command));
	EXPECT_TRUE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("DEL, ,-u, ,birthday,19900123");
	EXPECT_THROW(optionParser.getOptionType(command), invalid_argument);
}

TEST(OptionParserTest, checkPhoneNumOptionType)
{
	vector<string> command;
	CommandParser commandParser{};
	OptionParser optionParser{};

	command = commandParser.parseCommand("MOD, , , ,phoneNum,010-2321-1321,cl,CL4");
	EXPECT_EQ(OptionType::PHONE_NUM, optionParser.getOptionType(command));
	EXPECT_FALSE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("MOD, ,-m, ,phoneNum,010-2321-1321,cl,CL4");
	EXPECT_EQ(OptionType::MID_PHONE_NUM, optionParser.getOptionType(command));
	EXPECT_FALSE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("MOD,-p,-l, ,phoneNum,010-2321-1321,cl,CL4");
	EXPECT_EQ(OptionType::LAST_PHONE_NUM, optionParser.getOptionType(command));
	EXPECT_TRUE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("MOD,-p,-z, ,phoneNum,010-2321-1321,cl,CL4");
	EXPECT_THROW(optionParser.getOptionType(command), invalid_argument);
}


TEST(OptionParserTest, checkOtherOptionTest)
{
	vector<string> command;
	CommandParser commandParser{};
	OptionParser optionParser{};

	command = commandParser.parseCommand("SCH, , , ,cl,CL4");
	EXPECT_EQ(OptionType::LEVEL, optionParser.getOptionType(command));
	EXPECT_FALSE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("SCH,-p, , ,certi,PRO");
	EXPECT_EQ(OptionType::CERTI, optionParser.getOptionType(command));
	EXPECT_TRUE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("SCH,-p, , ,employeeNum,12039432");
	EXPECT_EQ(OptionType::EMPLOYEE_NUM, optionParser.getOptionType(command));
	EXPECT_TRUE(optionParser.hasPrintOption(command));

	command = commandParser.parseCommand("SCH,-p, , ,invalid,deadbeef");
	EXPECT_THROW(optionParser.getOptionType(command), invalid_argument);
}
