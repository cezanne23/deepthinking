#include "pch.h"
#include "../deep_thinking/Sorting.h"

TEST(SortingTest, PriorityQueueTest1) {
    vector<EmployeeInfo> employeeList = {
        { "80030189","XVDD CHUNG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "70040589","SDF LEE", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "99043189","EGKD ONG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "02045189","BKD NAMGUNG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "03980189","FDKFU OH", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "00070189","BZKCI KYE", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "01140189","PODNH GUN", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "10890189","KDVJN GOH", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69041189","ASF KIM", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "15034289","VKDIE JIN", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "21230189","ACGKE JANG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "90020189","VCXVD KOO", "CL3", "010-1221-5555", "19891210", "ADV" } };

    vector<EmployeeInfo> topFiveList = {
        { "69041189","ASF KIM", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "70040589","SDF LEE", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "80030189","XVDD CHUNG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "90020189","VCXVD KOO", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "99043189","EGKD ONG", "CL3", "010-1221-5555", "19891210", "ADV" },
    };

    PriorityQueue pq{};
    vector<EmployeeInfo> results{};
    int index = 0;

    pq.sort(employeeList);
    results = pq.getTopk();

    for (auto& result : results) {
        EXPECT_TRUE((result == topFiveList[index++]));
    }
}

TEST(SortingTest, PriorityQueueTest2) {
    vector<EmployeeInfo> employeeList = {
        { "69000015","XVDD CHUNG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000014","SDF LEE", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000013","EGKD ONG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000012","BKD NAMGUNG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000011","FDKFU OH", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000010","BZKCI KYE", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000009","PODNH GUN", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000008","KDVJN GOH", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000007","ASF KIM", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000006","VKDIE JIN", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000005","ACGKE JANG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000004","VCXVD KOO", "CL3", "010-1221-5555", "19891210", "ADV" } };

    vector<EmployeeInfo> topFiveList = {
        { "69000004","VCXVD KOO", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000005","ACGKE JANG", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000006","VKDIE JIN", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000007","ASF KIM", "CL3", "010-1221-5555", "19891210", "ADV" },
        { "69000008","KDVJN GOH", "CL3", "010-1221-5555", "19891210", "ADV" },
    };

    PriorityQueue pq{};
    vector<EmployeeInfo> results{};
    int index = 0;

    pq.sort(employeeList);
    results = pq.getTopk();

    for (auto& result : results) {
        EXPECT_TRUE((result == topFiveList[index++]));
    }
}
