#include "../deep_thinking/EmployeeManager.cpp"
#include "pch.h"


TEST(EmployeeManagerTest, fileValidationCheck) {
    EmployeeManager manager;
    EXPECT_EQ(manager.isVaildFilePath("input_20_20.txt"), 1);
    EXPECT_EQ(manager.isVaildFilePath("output_20_20.txt"), 1);
    EXPECT_EQ(manager.isVaildFilePath("../input.txt"), 0);
    EXPECT_EQ(manager.isVaildFilePath("../input.jpg"), 0);

    EXPECT_EQ(manager.setFilePath("input_20_20.txt", "output_20_20.txt"), 1);
    EXPECT_EQ(manager.setFilePath("../input.jpg", "output_20_20.txt"), 0);
}

TEST(EmployeeManagerTest, fileReadCheck) {
    EmployeeManager manager;
    string inputfile = "input_20.txt";
    string outputfile = "output_20_20.txt";
    manager.setFilePath(inputfile, outputfile);

    // There's no this inputfile. check the exception when try to open file
    EXPECT_THROW(manager.execute(), invalid_argument);

    inputfile = "input_20_20.txt";
    outputfile = "output_20_20.txt";
    manager.setFilePath(inputfile, outputfile);

    vector<string> strList = manager.execute();
    ASSERT_TRUE(strList.size());
    EXPECT_EQ(strList[0],
        "ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
    EXPECT_EQ(strList[1],
        "ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO");
    EXPECT_EQ(strList[9],
        "ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO");
}

TEST(EmployeeManagerTest, fileWriteCheck) {
    EmployeeManager manager;
    const string testfilepath = "testWriteFile.txt";
    ofstream ouputfile(testfilepath);
    manager.setFilePath("dummy.txt", testfilepath);

    //write file
    if (!ouputfile.is_open()) {
        cerr << "Could not open the file !! " << endl;
        ASSERT_FALSE(1);

    }
    const string testString[4] = { "SCH, 02117175, SBILHUT LDEXRI, CL4, 010 - 2814 - 1699, 19950704, ADV",
        "MOD, 17112609, FB NTAWR, CL4, 010 - 5645 - 6122, 19861203, PRO",
        "SCH, NONE",
        "DEL, 1"
    };
    for (const auto& result : testString) {
        manager.writeCommandResult(ouputfile, result);
    }
    ouputfile.close();

    //check the updated file
    ifstream input_file(testfilepath);
    if (!input_file.is_open()) {
        cerr << "Could not open the file !! " << endl;
        ASSERT_FALSE(1);
    }

    string line;
    int index = 0;
    while (std::getline(input_file, line)) {
        EXPECT_EQ(line, testString[index]);
        index++;
    }
    input_file.close();
}
