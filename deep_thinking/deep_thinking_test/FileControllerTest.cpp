#include "../deep_thinking/FileController.cpp"
#include "pch.h"


TEST(FileControllerTest, fileValidationCheck) {
    FileController fileController;
    EXPECT_EQ(fileController.isVaildFilePath("input_20_20.txt"), 1);
    EXPECT_EQ(fileController.isVaildFilePath("output_20_20.txt"), 1);
    EXPECT_EQ(fileController.isVaildFilePath("../input.txt"), 0);
    EXPECT_EQ(fileController.isVaildFilePath("../input.jpg"), 0);

    EXPECT_EQ(fileController.open("input_20_20.txt", "output_20_20.txt"), 1);
    fileController.close();
    EXPECT_EQ(fileController.open("../input.jpg", "output_20_20.txt"), 0);
    fileController.close();
}

TEST(FileControllerTest, fileReadCheck) {
    FileController fileController;
    string inputfile = "input_20.txt";
    string outputfile = "output_20_20.txt";
    

    // There's no this inputfile. check the exception when try to open file
    EXPECT_THROW(fileController.open(inputfile, outputfile), invalid_argument);
    fileController.close();

    inputfile = "input_20_20.txt";
    outputfile = "output_20_20.txt";
    fileController.open(inputfile, outputfile);

    string line;
    vector<string> strList;
    int count = 0;
    while ((line = fileController.getCommand()) != "" && count < 10) {
        strList.push_back(line);
        count++;
    }

    ASSERT_TRUE(strList.size());
    EXPECT_EQ(strList[0],
        "ADD, , , ,15123099,VXIHXOTH JHOP,CL3,010-3112-2609,19771211,ADV");
    EXPECT_EQ(strList[1],
        "ADD, , , ,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO");
    EXPECT_EQ(strList[9],
        "ADD, , , ,03113260,HH LTUPF,CL2,010-5798-5383,19791018,PRO");
    fileController.close();
}

TEST(FileControllerTest, fileWriteCheck) {
    FileController fileController;
    const string testfilepath = "testWriteFile.txt";
    fileController.open("input_20_20.txt", testfilepath);

    const string testString[4] = { "SCH, 02117175, SBILHUT LDEXRI, CL4, 010-2814-1699, 19950704, ADV",
        "MOD, 17112609, FB NTAWR, CL4, 010-5645-6122, 19861203, PRO",
        "SCH, NONE",
        "DEL, 1"
    };
    for (const auto& result : testString) {
        fileController.writeCommandResult(result);
    }
    fileController.close();

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
