#include "../deep_thinking/SearchEngine.cpp"
#include "pch.h"

#undef NOTRUN

class SearchEngineSingletonDBTest : public ::testing::Test {
protected:
	void SetUp() override {
		employDB = EmployeeDB::getDB();
		employDB->employeeList.clear();

		char strdata[] = "ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV\n\
ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO\n\
ADD, , , ,18115040,TTETHU HBO,CL3,010-4581-2050,20080718,ADV\n\
ADD, , , ,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO\n\
ADD, , , ,19129568,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO\n\
ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,PRO\n\
ADD, , , ,18117906,TWU QSOLT,CL4,010-6672-7186,20030413,PRO\n\
ADD, , , ,08123556,WN XV,CL1,010-7986-5047,20100614,PRO\n\
ADD, , , ,02117175,SBILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV\n\
ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO\n\
ADD, , , ,14130827,RPO JK,CL4,010-3231-1698,20090201,ADV\n\
ADD, , , ,01122329,DN WD,CL4,010-7174-5680,20071117,PRO\n\
ADD, , , ,08108827,RTAH VNUP,CL4,010-9031-2726,19780417,ADV\n\
ADD, , , ,85125741,FBAH RTIJ,CL1,010-8900-1478,19780228,ADV\n\
ADD, , , ,08117441,BMU MPOSXU,CL3,010-2703-3153,20010215,ADV\n\
ADD, , , ,10127115,KBU MHU,CL3,010-3284-4054,19660814,ADV\n\
ADD, , , ,12117017,LFIS JJIVL,CL1,010-7914-4067,20120812,PRO\n\
ADD, , , ,11125777,TKOQKIS HC,CL1,010-6734-2289,19991001,PRO\n\
ADD, , , ,11109136,QKAHCEX LTODDO,CL4,010-2627-8566,19640130,PRO\n\
ADD, , , ,05101762,VCUHLE HMU,CL4,010-3988-9289,20030819,PRO";

		vector<string> addlist = parser.split(strdata, '\n');
		for (auto st1 : addlist) {
			vector<string> data1 = parser.split(st1, ',');
			EmployeeInfo employee{ string(data1[4]), data1[5], data1[6], data1[7], data1[8], data1[9] };
			employDB->employeeList.insert({ data1[4],  employee });
		}
	};
	void TearDown() override {};
	SearchEngine searchEngine;
	EmployeeDB* employDB;
	InputParcer parser;
};

TEST_F(SearchEngineSingletonDBTest, singletonDBSizeTest) {
	EXPECT_EQ(employDB->employeeList.size(), 20);
	vector<string> res;
	InputParcer parser;

	res = searchEngine.searchID(parser.split("DEL, , , ,employeeNum,18115040", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "18115040");
	res.clear();;

	res = searchEngine.searchID(parser.split("DEL, , , ,employeeNum,18115040", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "18115040");
	res.clear();

	res = searchEngine.searchID(parser.split("SCH,-p,-l, ,name,MPOSXU", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "08117441");
	res.clear();
	res = searchEngine.searchID(parser.split("SCH, ,-f, ,name,VXIHXOTH", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "15123099");
	res.clear();

	res = searchEngine.searchID(parser.split("SCH,-p,-d, ,birthday,04", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "02117175");
	res.clear();

	res = searchEngine.searchID(parser.split("SCH, , , ,employeeNum,79110836", ','));
	ASSERT_EQ(res.size(), 0);
	res.clear();

	res = searchEngine.searchID(parser.split("DEL, , , ,employeeNum,18115040", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "18115040");
	res.clear();

	res = searchEngine.searchID(parser.split("SCH,-p, , ,certi,PRO", ','));
	ASSERT_EQ(res.size(), 12);
	res.clear();

	res = searchEngine.searchID(parser.split("SCH, , , ,certi,ADV", ','));
	ASSERT_EQ(res.size(), 8);
	res.clear();

	res = searchEngine.searchID(parser.split("SCH,-p, , ,cl,CL4", ','));
	ASSERT_EQ(res.size(), 9);

	res.clear();

	res = searchEngine.searchID(parser.split("SCH, ,-m, ,birthday,09", ','));
	ASSERT_EQ(res.size(), 1);
	res.clear();

	res = searchEngine.searchID(parser.split("MOD,-p, , ,name,FB NTAWR,cl,CL3", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "17112609");
	res.clear();

	res = searchEngine.searchID(parser.split("SCH, -p, -m, , phoneNum, 3112", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "15123099");
	res.clear();

	res = searchEngine.searchID(parser.split("SCH, -p, -l, , phoneNum, 8566", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "11109136");
	res.clear();
	
	res = searchEngine.searchID(parser.split("SCH, -p, , , phoneNum, 010-3988-9289", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "05101762");
	res.clear();
	
	res = searchEngine.searchID(parser.split("SCH, -p, , , birthday, 19991001", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "11125777");
	res.clear();
}

TEST(SearchEngineMaxDBTest, MaxDBTest) {
	EmployeeDB::getDB()->employeeList.clear();
	const size_t MAX_SIZE = 100000;
	string data = "ADD, , , ,05101762,VCUHLE HMU,CL4,010-3988-9289,20030819,PRO";
	InputParcer parser;
	vector<string> data1 = parser.split(data, ',');

	for (auto i = 0; i < MAX_SIZE; i++) {
		int num = i + 10000000;
		string id = to_string(num);
		EmployeeInfo employee{ id, data1[5], data1[6], data1[7], data1[8], data1[9] };
		EmployeeDB::getDB()->employeeList.insert({ id,  employee });
	}
}

TEST(SearchEngineMaxDBTest, MaxDBSerchNameTest) {
	SearchEngine searchEngine;
	InputParcer parser;
	
	string incmd;
	vector<string> ret, exp;

	incmd = "SCH, , , ,name,VCUHLE HMU";
	ret = searchEngine.searchID( parser.split(incmd, ','));
	EXPECT_EQ(100000, ret.size());
}

TEST(SearchEngineMaxDBTest, MaxDBSerchCLTest) {
	SearchEngine searchEngine;
	InputParcer parser;

	string incmd;
	vector<string> ret, exp;
	
	incmd = "SCH, , , ,cl,CL4";
	ret = searchEngine.searchID(parser.split(incmd, ','));
	EXPECT_EQ(100000, ret.size());
}

TEST(SearchEngineMaxDBTest, MaxDBSerchCertiTest) {
	SearchEngine searchEngine;
	InputParcer parser;

	string incmd;
	vector<string> ret, exp;

	incmd = "SCH, , , ,certi,PRO";
	ret = searchEngine.searchID(parser.split(incmd, ','));
	EXPECT_EQ(100000, ret.size());
}

TEST(SearchEngineMaxDBTest, MaxDBSerchBirthMonthTest) {
	SearchEngine searchEngine;
	InputParcer parser;

	string incmd;
	vector<string> ret, exp;

	incmd = "SCH, ,-m, ,birthday,08";
	ret = searchEngine.searchID(parser.split(incmd, ','));
	EXPECT_EQ(100000, ret.size());
}

class SearchEngineTest : public ::testing::Test {
protected:
	void SetUp() override {
		char strdata[] = "ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV\n\
ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO\n\
ADD, , , ,18115040,TTETHU HBO,CL3,010-4581-2050,20080718,ADV\n\
ADD, , , ,88114052,NQ LVARW,CL4,010-4528-3059,19911021,PRO\n\
ADD, , , ,19129568,SRERLALH HMEF,CL2,010-3091-9521,19640910,PRO\n\
ADD, , , ,17111236,VSID TVO,CL1,010-3669-1077,20120718,PRO\n\
ADD, , , ,18117906,TWU QSOLT,CL4,010-6672-7186,20030413,PRO\n\
ADD, , , ,08123556,WN XV,CL1,010-7986-5047,20100614,PRO\n\
ADD, , , ,02117175,SBILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV\n\
ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO\n\
ADD, , , ,14130827,RPO JK,CL4,010-3231-1698,20090201,ADV\n\
ADD, , , ,01122329,DN WD,CL4,010-7174-5680,20071117,PRO\n\
ADD, , , ,08108827,RTAH VNUP,CL4,010-9031-2726,19780417,ADV\n\
ADD, , , ,85125741,FBAH RTIJ,CL1,010-8900-1478,19780228,ADV\n\
ADD, , , ,08117441,BMU MPOSXU,CL3,010-2703-3153,20010215,ADV\n\
ADD, , , ,10127115,KBU MHU,CL3,010-3284-4054,19660814,ADV\n\
ADD, , , ,12117017,LFIS JJIVL,CL1,010-7914-4067,20120812,PRO\n\
ADD, , , ,11125777,TKOQKIS HC,CL1,010-6734-2289,19991001,PRO\n\
ADD, , , ,11109136,QKAHCEX LTODDO,CL4,010-2627-8566,19640130,PRO\n\
ADD, , , ,05101762,VCUHLE HMU,CL4,010-3988-9289,20030819,PRO";

		InputParcer parser;
		vector<string> addlist = parser.split(strdata, '\n');
		for (auto st1 : addlist) {
			vector<string> data1 = parser.split(st1, ',');
			EmployeeInfo employee{ string(data1[4]), data1[5], data1[6], data1[7], data1[8], data1[9] };
			employeeInfoDict.insert({ data1[4],  employee });
		}
	}

	void TearDown() override {}
	SearchEngine searchEngine;
	map<string, EmployeeInfo> employeeInfoDict;  // todo
};

TEST_F(SearchEngineTest, scenariTest) {
	EXPECT_EQ(employeeInfoDict.size(), 20);
	vector<string> res;
	InputParcer parser;

	res = searchEngine.seachID(employeeInfoDict, parser.split("DEL, , , ,employeeNum,18115040", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "18115040");
	res.clear();

	res = searchEngine.seachID(employeeInfoDict, parser.split("SCH,-p,-d, ,birthday,04", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "02117175");
	res.clear();

	res = searchEngine.seachID(employeeInfoDict, parser.split("SCH, , , ,employeeNum,79110836", ','));
	ASSERT_EQ(res.size(), 0);
	res.clear();

	res = searchEngine.seachID(employeeInfoDict, parser.split("DEL, , , ,employeeNum,18115040", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "18115040");
	res.clear();

	res = searchEngine.seachID(employeeInfoDict, parser.split("SCH,-p, , ,certi,PRO", ','));
	ASSERT_EQ(res.size(), 12);
	res.clear();

	res = searchEngine.seachID(employeeInfoDict, parser.split("SCH, , , ,certi,ADV", ','));
	ASSERT_EQ(res.size(), 8);
	res.clear();

	res = searchEngine.seachID(employeeInfoDict, parser.split("SCH,-p, , ,cl,CL4", ','));
	ASSERT_EQ(res.size(), 9);
	res.clear();

	res = searchEngine.seachID(employeeInfoDict, parser.split("SCH, ,-m, ,birthday,09", ','));
	ASSERT_EQ(res.size(), 1);
	res.clear();

	res = searchEngine.seachID(employeeInfoDict, parser.split("MOD,-p, , ,name,FB NTAWR,cl,CL3", ','));
	ASSERT_EQ(res.size(), 1);
	EXPECT_EQ(res[0], "17112609");
	res.clear();
}

TEST(SearchEngineParserTest, ParseTest) {
	InputParcer parser;

	string incmd("SCH, ,-m, ,birthday,09");
	vector<string> exp_ret = { "SCH","" ,"-m","" ,"birthday","09" };
	vector<string> ret = parser.split(incmd, ',');

	EXPECT_EQ(exp_ret, ret);
}
