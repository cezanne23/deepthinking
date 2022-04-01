#include "../deep_thinking/Command.cpp"
#include "../deep_thinking/EmployeeInfoManager.cpp"
#include "pch.h"

class CommandRunTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}

    AddCommmand addCommand;
    DeleteCommmand deleteCommand;
    ModifyCommmand modifyCommand;
    SearchCommmand searchCommand;
    map<int, EmployeeInfo> employeeInfo;
};

TEST_F(CommandRunTest, CommandTC) {
    // 3���� Employee �߰�
    EXPECT_EQ(addCommand.runCmd(
        employeeInfo,
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(addCommand.runCmd(
        employeeInfo,
        "ADD, , , ,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO"),
        "");
    EXPECT_EQ(addCommand.runCmd(
        employeeInfo,
        "ADD, , , ,17105065,DDDD EEEE,CL2,010-1234-5678,19900804,EX"),
        "");

    // CL3 ����
    EXPECT_EQ(deleteCommand.runCmd(employeeInfo, "DEL, , , ,cl,CL3"),
        "DeleteCommand" /*TODO : "DEL,2"*/);

    // CL3 �ٽ� �߰�
    EXPECT_EQ(addCommand.runCmd(
        employeeInfo,
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(addCommand.runCmd(
        employeeInfo,
        "ADD, , , ,15486152,KKKK BBBB,CL3,010-3355-7888,19780806,PRO"),
        "");

    // Ž�� Test
    EXPECT_EQ(searchCommand.runCmd(employeeInfo, "SCH,-p, , ,name,KYUMOK KIM"),
        "SearchCommand" /*TODO : "SCH,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO""*/);

    // ���� Test
    EXPECT_EQ(modifyCommand.runCmd(employeeInfo, "MOD,-p, , ,name,KYUMOK KIM,name,KYUMOK LEE"),
        "ModifyCommand" /*TODO : "MOD,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO""*/);
}

TEST(EmployeeInforManagerTC, EmployeeInforManagerTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "ExcuteCommand" /*TODO: ""*/);
}