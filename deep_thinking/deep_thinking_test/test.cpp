#include "pch.h"
#include "../deep_thinking/Command.cpp"
#include "../deep_thinking/EmployeeInfoManager.cpp"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(CommandTC, CommandTest) {
  map<int, EmployeeInfo> TestEmployees;

  AddCommmand* addCommand = new AddCommmand();
  DeleteCommmand* deleteCommand = new DeleteCommmand();
  ModifyCommmand* modifyCommand = new ModifyCommmand();
  SearchCommmand* searchCommand = new SearchCommmand();

  vector<ICommand*> commands;

  commands.push_back(addCommand);
  commands.push_back(deleteCommand);
  commands.push_back(modifyCommand);
  commands.push_back(searchCommand);

  const int addIndex = 0;
  const int delIndex = 1;
  const int modIndex = 2;
  const int schIndex = 3;

  // 3명의 Employee 추가
  EXPECT_EQ(commands.at(addIndex)->runCmd(
                TestEmployees,
                "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
            "");
  EXPECT_EQ(commands.at(addIndex)->runCmd(
                TestEmployees,
                "ADD, , , ,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO"),
            "");
  EXPECT_EQ(commands.at(addIndex)->runCmd(
                TestEmployees,
                "ADD, , , ,17105065,DDDD EEEE,CL2,010-1234-5678,19900804,EX"),
            "");

  // CL3 삭제
  EXPECT_EQ(commands.at(delIndex)->runCmd(TestEmployees, "DEL, , , ,cl,CL3"),
            "DeleteCommand" /*TODO : "DEL,2"*/);

  // CL3 다시 추가
  EXPECT_EQ(commands.at(addIndex)->runCmd(
                TestEmployees,
                "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
            "");
  EXPECT_EQ(commands.at(addIndex)->runCmd(
                TestEmployees,
                "ADD, , , ,15486152,KKKK BBBB,CL3,010-3355-7888,19780806,PRO"),
            "");

  // 탐색 Test
  EXPECT_EQ(commands.at(schIndex)->runCmd(TestEmployees, "SCH,-p, , ,name,KYUMOK KIM"),
            "SearchCommand" /*TODO : "SCH,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO""*/);

  // 수정 Test
  EXPECT_EQ(commands.at(modIndex)->runCmd(TestEmployees, "MOD,-p, , ,name,KYUMOK KIM,name,KYUMOK LEE"),
            "ModifyCommand" /*TODO : "MOD,15486152,KYUMOK KIM,CL3,010-3355-7888,19780806,PRO""*/);

  delete addCommand;
  delete deleteCommand;
  delete modifyCommand;
  delete searchCommand;
}

TEST(EmployeeInforManagerTC, EmployeeInforManagerTest) {
  EmployeeInfoManager* employeeInfoManager = new EmployeeInfoManager();

  EXPECT_EQ(employeeInfoManager->ExcuteCommand(
                "ADD, , , ,18050301,AAAA BBBB,CL3,010-9777-6055,19980906,PRO"),
            "ExcuteCommand" /*TODO: ""*/);
}