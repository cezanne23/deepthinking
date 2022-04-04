#include "../deep_thinking/Command.cpp"
#include "../deep_thinking/EmployeeInfoManager.cpp"
#include "pch.h"

class CommandRunTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
    AddCommand addCommand;
    DeleteCommand deleteCommand;
    ModifyCommand modifyCommand;
    SearchCommand searchCommand;
    map<string, EmployeeInfo> employeeInfo;
};

TEST_F(CommandRunTest, CommandTC) {
    vector<string> command;
    command.clear();
    command.push_back("ADD");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("18050301");
    command.push_back("AAAA BBBB");
    command.push_back("CL3");
    command.push_back("010-9777-6055");
    command.push_back("19980906");
    command.push_back("PRO");
    // 3명의 Employee 추가
    EXPECT_EQ(addCommand.runCmd(command), "");

    command.clear();
    command.push_back("ADD");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("15486152");
    command.push_back("KYUMOK KIM");
    command.push_back("CL3");
    command.push_back("010-3355-7888");
    command.push_back("19780806");
    command.push_back("PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command.clear();
    command.push_back("ADD");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("17105065");
    command.push_back("DDDD EEEE");
    command.push_back("CL2");
    command.push_back("010-1234-5678");
    command.push_back("19900804");
    command.push_back("EX");
    EXPECT_EQ(addCommand.runCmd(command), "");

    // CL3 삭제
    command.clear();
    command.push_back("DEL");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("cl");
    command.push_back("CL3");
    EXPECT_EQ(deleteCommand.runCmd(command), "2");

    command.clear();
    command.push_back("ADD");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("15486152");
    command.push_back("KYUMOK KIM");
    command.push_back("CL3");
    command.push_back("010-3355-7888");
    command.push_back("19780806");
    command.push_back("PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command.clear();
    command.push_back("ADD");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("17105065");
    command.push_back("DDDD EEEE");
    command.push_back("CL2");
    command.push_back("010-1234-5678");
    command.push_back("19900804");
    command.push_back("EX");
    EXPECT_EQ(addCommand.runCmd(command), "");

    // 탐색 Test
    command.clear();
    command.push_back("SCH");
    command.push_back("-p");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("name");
    command.push_back("KYUMOK KIM");
    EXPECT_EQ(searchCommand.runCmd(command), "SearchCommand" /*TODO : "SCH,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO""*/);

    // 수정 Test
    command.clear();
    command.push_back("MOD");
    command.push_back("-p");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("name");
    command.push_back("KYUMOK KIM");
    command.push_back("name");
    command.push_back("KYUMOK LEE");
    EXPECT_EQ(modifyCommand.runCmd(command), "ModifyCommand" /*TODO : "MOD,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO""*/);
}

TEST(EmployeeInforManagerTC, EmployeeInforManagerTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,cl,CL3,name,AAAA CCCC"),
        "ModifyCommand");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "SCH, , , ,name,AAAA CCCC"),
        "SearchCommand");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "DEL, , , ,name,AAAA CCCC"),
        "NONE");
}

TEST(EmployeeInforManagerTC, EmployeeInforDELTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EmployeeDB::getDB()->employeeList.clear();
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050302,AAAA CCCC,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050303,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050304,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "DEL, , , ,name,AAAA CCCC"),
        "1");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "DEL, , , ,phoneNum,010-9777-6055"),
        "3");

    EXPECT_EQ(EmployeeDB::getDB()->employeeList.size(), 0);

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050302,AAAA CCCC,CL3,010-9777-6056,19981206,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050303,AAAA BBBB,CL3,010-9777-6057,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050304,AAAA BBBB,CL3,010-9777-6058,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050305,AAAA BBBB,CL3,010-9777-6059,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050306,AAAA BBBB,CL3,010-9777-6010,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050307,AAAA BBBB,CL3,010-9000-6010,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "DEL,-p, , ,birthday,19980906"),
        "DEL,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO\nDEL,18050303,AAAA BBBB,CL3,010-9777-6057,19980906,PRO\nDEL,18050304,AAAA BBBB,CL3,010-9777-6058,19980906,PRO\nDEL,18050305,AAAA BBBB,CL3,010-9777-6059,19980906,PRO\nDEL,18050306,AAAA BBBB,CL3,010-9777-6010,19980906,PRO");
}

