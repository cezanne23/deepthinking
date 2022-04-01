#include "pch.h"
#include "../deep_thinking/EmployeeManager.cpp"

#include <string>
#include <vector>
using namespace std;

TEST(EmployeeManagerTest, 파일경로유효성검사) {
  EmployeeManager manager;

  EXPECT_EQ(manager.isVaildFilePath("input_20_20.txt"), 1);
  EXPECT_EQ(manager.isVaildFilePath("output_20_20.txt"), 1);
  EXPECT_EQ(manager.isVaildFilePath("../input.txt"), 0);
  EXPECT_EQ(manager.isVaildFilePath("../input.jpg"), 0);

  EXPECT_EQ(manager.setFilePath("input_20_20.txt", "output_20_20.txt"), 1);
  EXPECT_EQ(manager.setFilePath("../input.jpg", "output_20_20.txt"), 0);
}

