#include "pch.h"
#include "../deep_thinking/Sorting.h"

#include <random>

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

    index = 0;
    for (auto& result : pq.sort_partial(employeeNumList, 5)) {
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

    index = 0;
    for (auto& result : pq.sort_partial(employeeNumList, 5)) {
        EXPECT_TRUE((result == topFiveList[index++]));
    }
}
class FixtureSortingRandNumGenerator : public ::testing::Test {
protected:
    void SetUp() override {
        pq_results.clear();
        sort_partial_results.clear();
        testvector.clear();

        random_device rd;
        mt19937_64 mt(rd());
        uniform_int_distribution<size_t> randomNum(0, 1000000);

        testvector.reserve(max_size);
        for (int i = 0; i < max_size; ++i) {
            size_t randVal = baseNum + randomNum(mt);
            testvector.emplace_back(to_string(randVal));
        }
    }
    void TearDown() override {
    }
public:
    vector<string> testvector;
    vector<string> pq_results;
    vector<string> sort_partial_results;
    const size_t baseNum = 69000000;
    const size_t max_size = 50000;
};

TEST_F(FixtureSortingRandNumGenerator, PriorityQueuePerformanceTest) 
{
    PriorityQueue pq{};
    vector<string> pq_results;

    pq.sort(testvector);
    pq_results = pq.getTopk(5);
    // For Measuring Peformance
    EXPECT_EQ(1, 1);
}

TEST_F(FixtureSortingRandNumGenerator, SortPartialPerformanceTest)
{
    PriorityQueue pq{};
    vector<string> partial_sort_results;

    partial_sort_results = pq.sort_partial(testvector, 5);
    // For Measuring Peformance
    EXPECT_EQ(1, 1);
}

TEST_F(FixtureSortingRandNumGenerator, SortResultsValidationTest)
{
    PriorityQueue pq{};
    vector<string> pq_results;

    pq.sort(testvector);
    pq_results = pq.getTopk(5);

    vector<string> partial_sort_results;
    partial_sort_results = pq.sort_partial(testvector, 5);

    EXPECT_EQ(pq_results, partial_sort_results);
}