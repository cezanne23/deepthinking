#include "../deep_thinking/Command.cpp"
#include "../deep_thinking/EmployeeInfoManager.cpp"
#include "pch.h"

class CommandRunTest : public ::testing::Test {
protected:
    void SetUp() override {
        EmployeeDB::getDB()->employeeList.clear();
    }

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
    EXPECT_EQ(deleteCommand.runCmd(command), "DEL,7");

    // 탐색 Test
    command = commandParser.parseCommand("SCH,-p, , ,name,KYUMOK KIM");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,NONE");

    // Employee 추가
    command = commandParser.parseCommand("ADD, , , ,96486152,KYUMOK KIM,CL2,010-3355-7888,19780806,PRO");
    EXPECT_EQ(addCommand.runCmd(command), "");

    // 수정 Test

    command = commandParser.parseCommand("MOD,-p, , ,name,KYUMOK KIM,name,KYUMOK LEE");
    EXPECT_EQ(modifyCommand.runCmd(command), "MOD,96486152,KYUMOK KIM,CL2,010-3355-7888,19780806,PRO" );

}

TEST(EmployeeInforManagerTC, EmployeeInforManagerTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "SCH, , , ,name,AAAA BBBB"),
        "SCH,1");

    // EXPECT_EQ(employeeInfoManager->ExcuteCommand(
    //     "MOD, , , ,cl,CL3,name,AAAA CCCC"),
    //     "ModifyCommand");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "SCH, , , ,name,AAAA BBBB"),
        // Modify 구현 이후 수정 필요
        "SCH,1");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "DEL, , , ,name,AAAA CCCC"),
        "DEL,NONE");
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
        "DEL,1");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "DEL, , , ,phoneNum,010-9777-6055"),
        "DEL,3");

    EXPECT_EQ(EmployeeDB::getDB()->employeeList.size(), 0);

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050302,AAAA CCCC,CL3,010-9777-6056,19971206,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050305,AAAA BBBB,CL3,010-9777-6057,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050307,AAAA BBBB,CL3,010-9777-6058,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050304,AAAA BBBB,CL3,010-9777-6059,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050306,AAAA BBBB,CL3,010-9777-6010,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050303,AAAA BBBB,CL3,010-9000-6010,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "DEL,-p, , ,birthday,19980906"),
        "DEL,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO\nDEL,18050303,AAAA BBBB,CL3,010-9000-6010,19980906,PRO\nDEL,18050304,AAAA BBBB,CL3,010-9777-6059,19980906,PRO\nDEL,18050305,AAAA BBBB,CL3,010-9777-6057,19980906,PRO\nDEL,18050306,AAAA BBBB,CL3,010-9777-6010,19980906,PRO");
}

TEST(EmployeeInforManagerTC, EmployeeInforMODTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EmployeeDB::getDB()->employeeList.clear();
    map<string, EmployeeInfo> eDB =  EmployeeDB::getDB()->employeeList;
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");
    
    EXPECT_EQ(1, EmployeeDB::getDB()->employeeList.size());
   
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p, , ,birthday,19980906,birthday,19980926"),
        "MOD,18050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,FB NTAWR,birthday,20050520"),
        "MOD,1");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p, , ,name,FB NTAWR,birthday,20150520"),
        "MOD,18050301,FB NTAWR,CL3,010-9777-6055,20050520,PRO");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,FB NTAWRAA,birthday,20150524"),
        "MOD,NONE");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p, , ,name,FB NTAWRAA,birthday,20120524"),
        "MOD,NONE");


    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,FB NTAWR,name,AAA BBBB"),
        "MOD,1");

    // 
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p, , ,name,AAA BBBB,name,EEEE FFF"),
        "MOD,18050301,AAA BBBB,CL3,010-9777-6055,20150520,PRO");
    // 
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p, , ,name,EEEE FFF,name,AAA BBBB"),
        "MOD,18050301,EEEE FFF,CL3,010-9777-6055,20150520,PRO");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,AAA BBBB,cl,CL4"),
        "MOD,1");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,AAA BBBB,phoneNum,010-1234-5678"),
        "MOD,1"); 
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,AAA BBBB,certi,ADV"),
        "MOD,1"); 
    EXPECT_EQ(employeeInfoManager->ExcuteCommand( // employeeNum should not change
        "MOD, , , ,name,AAA BBBB,employeeNum,12345678"),
        "MOD,1");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand( 
        "MOD, , , ,employeeNum,12345678,phoneNum,010-4567-1234"),
        "MOD,NONE");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050310,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,21050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,69050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,99050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050305,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,84050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p, , ,certi,PRO,cl,CL4"),
        string("MOD,69050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO\n") +
        string("MOD,84050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO\n") +
        string("MOD,99050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO\n") +
        string("MOD,18050305,FB NTAWR,CL3,010-9777-6055,19980906,PRO\n") +
        string("MOD,18050310,FB NTAWR,CL3,010-9777-6055,19980906,PRO")
    );

}

TEST(EmployeeInforManagerTC, EmployeeInforMODSchBirthTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EmployeeDB::getDB()->employeeList.clear();
    map<string, EmployeeInfo> eDB = EmployeeDB::getDB()->employeeList;
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");

    EXPECT_EQ(1, EmployeeDB::getDB()->employeeList.size());
    
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p, , ,birthday,19980906,name,AAA BBBB"),
        "MOD,18050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,birthday,19980906,name,BB CCC"),
        "MOD,1");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p,-d, ,birthday,06,name,CC DDD"),
        "MOD,18050301,BB CCC,CL3,010-9777-6055,19980906,PRO");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p,-m, ,birthday,09,name,DD EEE"),
        "MOD,18050301,CC DDD,CL3,010-9777-6055,19980906,PRO");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p,-y, ,birthday,1998,name,BIR TH09"),
        "MOD,18050301,DD EEE,CL3,010-9777-6055,19980906,PRO");
}

TEST(EmployeeInforManagerTC, EmployeeInforMODPrintTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EmployeeDB::getDB()->employeeList.clear();
    map<string, EmployeeInfo> eDB = EmployeeDB::getDB()->employeeList;
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");

    EXPECT_EQ(1, EmployeeDB::getDB()->employeeList.size());

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p,-f, ,name,FB,cl,CL1"),
        "MOD,18050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p,-l, ,name,NTAWR,phoneNum,010-9777-1111"),
        "MOD,18050301,FB NTAWR,CL1,010-9777-6055,19980906,PRO");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD,-p, , ,name,FB NTAWR,birthday,21980906"),
        "MOD,18050301,FB NTAWR,CL1,010-9777-1111,19980906,PRO");

}