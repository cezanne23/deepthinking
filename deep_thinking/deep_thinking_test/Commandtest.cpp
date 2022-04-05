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

    CommandParser commandParser;
};

TEST_F(CommandRunTest, CommandTC) {
    vector<string> command;

    // Employee ADD
    command = commandParser.parseCommand("ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command = commandParser.parseCommand("ADD, , , ,12486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command = commandParser.parseCommand("ADD, , , ,96486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command = commandParser.parseCommand("ADD, , , ,93486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command = commandParser.parseCommand("ADD, , , ,69486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command = commandParser.parseCommand("ADD, , , ,20486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command = commandParser.parseCommand("ADD, , , ,06486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    command = commandParser.parseCommand("ADD, , , ,17105065,DDDD EEEE,CL2,010-1234-5678,19900804,EX");
    EXPECT_EQ(addCommand.runCmd(command), "");

    // 탐색 Test
    command = commandParser.parseCommand("SCH, , , ,name,AAAA BBBB");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,1");

    command = commandParser.parseCommand("SCH, , , ,name,KYUMOK KIM");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,6");

    command = commandParser.parseCommand("SCH,-p, , ,name,KYUMOK KIM");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,69486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\n\
SCH,93486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\n\
SCH,96486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\n\
SCH,06486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\n\
SCH,12486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");

    command = commandParser.parseCommand("SCH, , , ,cl,CL3");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,7");

    command = commandParser.parseCommand("SCH,-p, , ,cl,CL3");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,69486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\n\
SCH,93486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\n\
SCH,96486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\n\
SCH,06486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\n\
SCH,12486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");

    // CL3 삭제
    command = commandParser.parseCommand("DEL, , , ,cl,CL3");
    EXPECT_EQ(deleteCommand.runCmd(command), "7");

    // 탐색 Test
    command = commandParser.parseCommand("SCH,-p, , ,name,KYUMOK KIM");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,NONE");

    // Employee 추가
    command = commandParser.parseCommand("ADD, , , ,96486152,KYUMOK KIM,CL2,010-3355-7888,19780806,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    // 수정 Test
    command = commandParser.parseCommand("MOD,-p, , ,name,KYUMOK KIM,name,KYUMOK LEE");
    EXPECT_EQ(modifyCommand.runCmd(command), "ModifyCommand" /*TODO : "MOD,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO""*/);
}

TEST(EmployeeInforManagerTC, EmployeeInforManagerTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "SCH, , , ,name,AAAA BBBB"),
        "SCH,1");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,cl,CL3,name,AAAA CCCC"),
        "ModifyCommand");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "SCH, , , ,name,AAAA BBBB"),
        // Modify 구현 이후 수정 필요
        "SCH,1");

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

