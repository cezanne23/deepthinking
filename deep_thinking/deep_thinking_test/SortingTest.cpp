#include "pch.h"
#include "../deep_thinking/Sorting.h"

TEST(SortingTest, PriorityQueueTest1) {
    vector<string> employeeNumList = { "80030189","70040589","99043189","02045189", "03980189", "00070189", "01140189", "10890189",
                                       "69041189","15034289","21230189","90020189" };
    vector<string> topFiveList = { "69041189","70040589","80030189","90020189","99043189" };

    PriorityQueue pq{};
    vector<string> results{};
    int index = 0;

    pq.sort(employeeNumList);
    results = pq.getTopk();

    for (auto& result : results) {
        EXPECT_TRUE((result == topFiveList[index++]));
    }
}

TEST(SortingTest, PriorityQueueTest2) {
    vector<string> employeeNumList = { "69000015", "69000014", "69000013", "69000012", "69000011", "69000010",
                                       "69000009", "69000008", "69000007", "69000006", "69000005", "69000004" };
    vector<string> topFiveList = { "69000004","69000005","69000006","69000007","69000008" };

    PriorityQueue pq{};
    vector<string> results{};
    int index = 0;

    pq.sort(employeeNumList);
    results = pq.getTopk();

    for (auto& result : results) {
        EXPECT_TRUE((result == topFiveList[index++]));
    }
}
