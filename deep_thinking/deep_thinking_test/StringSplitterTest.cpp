#include "pch.h"
#include "../deep_thinking/StringSplitter.h"

TEST(StringSplitter, SplitCommandTest) {
    const char EMPTY = ' ';
    const char COMMA = ',';
    const char DASH = '-';

    const string addCommand = "ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV";

    vector<string> result;
    vector<string> splitted_result = StringSplitter().splitString(addCommand, COMMA);

    EXPECT_EQ("ADD", splitted_result[0]);

    result.clear();
    result = StringSplitter().splitString(splitted_result[5], EMPTY);

    EXPECT_EQ("VXIHXOTH", result[0]);
    EXPECT_EQ("JHOP", result[1]);

    result.clear();
    result = StringSplitter().splitString(splitted_result[7], DASH);

    EXPECT_EQ("3112", result[1]);
    EXPECT_EQ("2609", result[2]);
}