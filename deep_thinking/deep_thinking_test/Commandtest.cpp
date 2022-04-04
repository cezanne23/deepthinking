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
};

TEST_F(CommandRunTest, CommandTC) {
    vector<string> command;

    // 3명의 Employee 추가
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
    EXPECT_EQ(addCommand.runCmd(command), "");

    command.clear();
    command.push_back("ADD");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("96486152");
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
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("name");
    command.push_back("KYUMOK KIM");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,1");

    command.clear();
    command.push_back("SCH");
    command.push_back("-p");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("name");
    command.push_back("KYUMOK KIM");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,96486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO");

    command.clear();
    command.push_back("SCH");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("cl");
    command.push_back("CL3");
    EXPECT_EQ(searchCommand.runCmd(command), "SCH,2");

    command.clear();
    command.push_back("SCH");
    command.push_back("-p");
    command.push_back(" ");
    command.push_back(" ");
    command.push_back("cl");
    command.push_back("CL3");
    string str = "SCH,96486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO\nSCH,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO";
    EXPECT_EQ(searchCommand.runCmd(command), 
        str);

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
    command.push_back("96486152");
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
    // TODO : Delete 구현 이후 확인 필요 
    //EXPECT_EQ(searchCommand.runCmd(command), "SCH,NONE");

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
    // move seperat TC EXPECT_EQ(modifyCommand.runCmd(command), "ModifyCommand" /*TODO : "MOD,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO""*/);
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

TEST(EmployeeInforManagerTC, EmployeeInforMODTest) {
    EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

    EmployeeDB::getDB()->employeeList.clear();
    map<string, EmployeeInfo> eDB =  EmployeeDB::getDB()->employeeList;
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "ADD, , , ,18050301,FB NTAWR,CL3,010-9777-6055,19980906,PRO"),
        "");
    
    EXPECT_EQ(1, EmployeeDB::getDB()->employeeList.size());
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,FB NTAWR,birthday,20050520"),
        "MOD,1");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,FB NTAWRAA,birthday,20150524"),
        "MOD,NONE");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,FB NTAWR,name,AAA BBBB"),
        "MOD,1");

    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,AAA BBBB,cl,CL4"),
        "MOD,1");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,AAA BBBB,phoneNum,010-1234-5678"),
        "MOD,1"); 
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,AAA BBBB,certi,ADV"),
        "MOD,1");
    EXPECT_EQ(employeeInfoManager->ExcuteCommand(
        "MOD, , , ,name,AAA BBBB,employeeNum,12345678"),
        "MOD,1");
}

