#include "../deep_thinking/SearchEngine.cpp"
#include "pch.h"

class SearchEngineTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  void TearDown() override {}
  SearchEngine searchEngine;
  map<int, EmployeeInfo> employeeInfo;  // todo
};

TEST_F(SearchEngineTest, IsEmptyInitially) {
  vector<int> res = searchEngine.seachID(employeeInfo, "abc");
  EXPECT_EQ(res.size(), 0);
  EXPECT_EQ(employeeInfo.size(), 0);
}
