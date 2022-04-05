#include "../deep_thinking/Command.h"
#include "pch.h"

TEST(MODUpdateTest, updateTest) {
    EmployeeInfo test = { "18040189","San LEE", "CL3", "010-1221-5555", "19981010", "ADV" };
    const string info[6] = { "22040189","DEEP Park", "CL1", "010-2134-5678", "20001010", "EX" };
    MODUpdate* update = nullptr;

    update = new MODUpdateName;
    update->update(test, "DEEP Park");
    EXPECT_EQ(test.getName(), "DEEP Park");
    delete update;

    update = new MODUpdateLevel;
    update->update(test, "CL1");
    EXPECT_EQ(test.getLevel(), "CL1");
    delete update;

    update = new MODUpdatePhoneNum;
    update->update(test, "010-2134-5678");
    EXPECT_EQ(test.getPhoneNum(), "010-2134-5678");
    delete update;

    update = new MODUpdateBirth;
    update->update(test, "20001010");
    EXPECT_EQ(test.getBirthDate(), "20001010");
    delete update;

    update = new MODUpdateCerti;
    update->update(test, "EX");
    EXPECT_EQ(test.getCerti(), "EX");
    delete update;

    update = new MODUpdateEmployeeNum;
    update->update(test, "22040189");
    EXPECT_EQ(test.getEmployeeNum(), "18040189");
    delete update;
}

