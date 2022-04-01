#include "../deep_thinking/SearchEngine.cpp"
#include "pch.h"

class SearchEngineTest : public ::testing::Test {
protected:
	void SetUp() override {
		char strdata[] = "ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV\n\
		ADD, , , , 17112609, FB NTAWR, CL4, 010 - 5645 - 6122, 19861203, PRO\n\
		ADD, , , , 18115040, TTETHU HBO, CL3, 010 - 4581 - 2050, 20080718, ADV\n\
		ADD, , , , 88114052, NQ LVARW, CL4, 010 - 4528 - 3059, 19911021, PRO\n\
		ADD, , , , 19129568, SRERLALH HMEF, CL2, 010 - 3091 - 9521, 19640910, PRO\n\
		ADD, , , , 17111236, VSID TVO, CL1, 010 - 3669 - 1077, 20120718, PRO\n\
		ADD, , , , 18117906, TWU QSOLT, CL4, 010 - 6672 - 7186, 20030413, PRO\n\
		ADD, , , , 08123556, WN XV, CL1, 010 - 7986 - 5047, 20100614, PRO\n\
		ADD, , , , 02117175, SBILHUT LDEXRI, CL4, 010 - 2814 - 1699, 19950704, ADV\n\
		ADD, , , , 03113260, HH LTUPF, CL2, 010 - 5798 - 5383, 19791018, PRO\n\
		ADD, , , , 14130827, RPO JK, CL4, 010 - 3231 - 1698, 20090201, ADV\n\
		ADD, , , , 01122329, DN WD, CL4, 010 - 7174 - 5680, 20071117, PRO\n\
		ADD, , , , 08108827, RTAH VNUP, CL4, 010 - 9031 - 2726, 19780417, ADV\n\
		ADD, , , , 85125741, FBAH RTIJ, CL1, 010 - 8900 - 1478, 19780228, ADV\n\
		ADD, , , , 08117441, BMU MPOSXU, CL3, 010 - 2703 - 3153, 20010215, ADV\n\
		ADD, , , , 10127115, KBU MHU, CL3, 010 - 3284 - 4054, 19660814, ADV\n\
		ADD, , , , 12117017, LFIS JJIVL, CL1, 010 - 7914 - 4067, 20120812, PRO\n\
		ADD, , , , 11125777, TKOQKIS HC, CL1, 010 - 6734 - 2289, 19991001, PRO\n\
		ADD, , , , 11109136, QKAHCEX LTODDO, CL4, 010 - 2627 - 8566, 19640130, PRO\n\
		ADD, , , , 05101762, VCUHLE HMU, CL4, 010 - 3988 - 9289, 20030819, PRO";

		InputParcer parser;
		vector<string> addlist = parser.split(strdata, '\n');
		for (auto st1 : addlist) {
			vector<string> data1 = parser.split(st1, ',');
			EmployeeInfo employee{ string(data1[4]), data1[5], data1[6], data1[7], data1[8], data1[9] };
			employeeInfoDict.insert({ atoi(data1[4].c_str()),  employee });
		}
	}

	void TearDown() override {}
	SearchEngine searchEngine;
	map<int, EmployeeInfo> employeeInfoDict;  // todo
};

TEST_F(SearchEngineTest, IsEmptyInitially) {
	EXPECT_EQ(employeeInfoDict.size(), 0);

	vector<int> resid = searchEngine.seachID(employeeInfoDict, "SCH, , , ,employeeNum,79110836");
	ASSERT_EQ(resid.size(), 1);
	EXPECT_EQ(resid[0], 590);

	vector<int> resname = searchEngine.seachID(employeeInfoDict, "DEL,-p,-l, ,name,MPOSXU");
	ASSERT_EQ(resname.size(), 1);
	EXPECT_EQ(resname[0], 591);

	vector<int> respro = searchEngine.seachID(employeeInfoDict, "SCH,-p, , ,certi,PRO");
	ASSERT_EQ(respro.size(), 1);
	EXPECT_EQ(respro[0], 594);
}

TEST(SearchEngineParserTest, ParseTest) {
	InputParcer parser;

	string incmd("SCH, ,-m, ,birthday,09");
	vector<string> exp_ret = { "SCH"," " ,"-m"," " ,"birthday","09" };
	vector<string> ret = parser.split(incmd, ',');

	EXPECT_EQ(exp_ret, ret);
}

TEST(LargeStringTest, dataTest) {
	char strdata[] = "ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV\n\
		ADD, , , , 17112609, FB NTAWR, CL4, 010 - 5645 - 6122, 19861203, PRO\n\
		ADD, , , , 18115040, TTETHU HBO, CL3, 010 - 4581 - 2050, 20080718, ADV\n\
		ADD, , , , 88114052, NQ LVARW, CL4, 010 - 4528 - 3059, 19911021, PRO\n\
		ADD, , , , 19129568, SRERLALH HMEF, CL2, 010 - 3091 - 9521, 19640910, PRO\n\
		ADD, , , , 17111236, VSID TVO, CL1, 010 - 3669 - 1077, 20120718, PRO\n\
		ADD, , , , 18117906, TWU QSOLT, CL4, 010 - 6672 - 7186, 20030413, PRO\n\
		ADD, , , , 08123556, WN XV, CL1, 010 - 7986 - 5047, 20100614, PRO\n\
		ADD, , , , 02117175, SBILHUT LDEXRI, CL4, 010 - 2814 - 1699, 19950704, ADV\n\
		ADD, , , , 03113260, HH LTUPF, CL2, 010 - 5798 - 5383, 19791018, PRO\n\
		ADD, , , , 14130827, RPO JK, CL4, 010 - 3231 - 1698, 20090201, ADV\n\
		ADD, , , , 01122329, DN WD, CL4, 010 - 7174 - 5680, 20071117, PRO\n\
		ADD, , , , 08108827, RTAH VNUP, CL4, 010 - 9031 - 2726, 19780417, ADV\n\
		ADD, , , , 85125741, FBAH RTIJ, CL1, 010 - 8900 - 1478, 19780228, ADV\n\
		ADD, , , , 08117441, BMU MPOSXU, CL3, 010 - 2703 - 3153, 20010215, ADV\n\
		ADD, , , , 10127115, KBU MHU, CL3, 010 - 3284 - 4054, 19660814, ADV\n\
		ADD, , , , 12117017, LFIS JJIVL, CL1, 010 - 7914 - 4067, 20120812, PRO\n\
		ADD, , , , 11125777, TKOQKIS HC, CL1, 010 - 6734 - 2289, 19991001, PRO\n\
		ADD, , , , 11109136, QKAHCEX LTODDO, CL4, 010 - 2627 - 8566, 19640130, PRO\n\
		ADD, , , , 05101762, VCUHLE HMU, CL4, 010 - 3988 - 9289, 20030819, PRO";

	InputParcer parser;
	vector<string> addlist = parser.split(strdata, '\n');
	for (auto st1 : addlist) {
		cout << st1 << endl;
		vector<string> data1 = parser.split(st1, ',');
		for (auto st2 : data1) {
			cout << st2 << endl;
		}

	}
}