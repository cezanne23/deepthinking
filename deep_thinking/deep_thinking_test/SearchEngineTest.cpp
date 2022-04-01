#include "../deep_thinking/SearchEngine.cpp"
#include "pch.h"

class SearchEngineTest : public ::testing::Test {
protected:
	void SetUp() override {}

	void TearDown() override {}
	SearchEngine searchEngine;
	map<int, EmployeeInfo> employeeInfo;  // todo
};

TEST_F(SearchEngineTest, IsEmptyInitially) {
	EXPECT_EQ(employeeInfo.size(), 0);

	vector<int> resid = searchEngine.seachID(employeeInfo, "SCH, , , ,employeeNum,79110836");
	ASSERT_EQ(resid.size(), 1);
	EXPECT_EQ(resid[0], 590);

	vector<int> resname = searchEngine.seachID(employeeInfo, "DEL,-p,-l, ,name,MPOSXU");
	ASSERT_EQ(resname.size(), 1);
	EXPECT_EQ(resname[0], 591);

	vector<int> respro = searchEngine.seachID(employeeInfo, "SCH,-p, , ,certi,PRO");
	ASSERT_EQ(respro.size(), 1);
	EXPECT_EQ(respro[0], 594);
}

TEST(SearchEngineParserTest, ParseTest) {
	InputParcer parser;

	string incmd("SCH, ,-m, ,birthday,09");
	vector<string> exp_ret = { "SCH"," " ,"-m"," " ,"birthday","09" };
	vector<string> ret = parser.split(incmd);

	EXPECT_EQ(exp_ret, ret);
}