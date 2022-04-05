#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#include "EmployeeInfo.h"

using namespace std;

class ISorting {
public:
    virtual void sort(vector<string> list) = 0;
    virtual vector<string> sort_partial(vector<string> list, size_t k = 5) = 0;
    virtual vector<string> getTopk(size_t k = 5) = 0;
};

struct cmp_greater {
    bool operator()(string a, string b) {
        if (getULemployeeNum(a) > getULemployeeNum(b)) {
            return true;
        }
        return false;
    }

    size_t getULemployeeNum(const string& employeeNum) const {
        const size_t numThreshold = 69000000;
        size_t employeeNum_UL = stoul(employeeNum.c_str());
        if (employeeNum_UL < numThreshold) {
            employeeNum_UL += numThreshold;
        }
        else {
            employeeNum_UL -= numThreshold;
        }
        return employeeNum_UL;
    }
};

struct cmp_less {
    bool operator()(string a, string b) {
        if (getULemployeeNum(a) < getULemployeeNum(b)) {
            return true;
        }
        return false;
    }

    size_t getULemployeeNum(const string& employeeNum) const {
        const size_t numThreshold = 69000000;
        size_t employeeNum_UL = stoul(employeeNum.c_str());
        if (employeeNum_UL < numThreshold) {
            employeeNum_UL += numThreshold;
        }
        else {
            employeeNum_UL -= numThreshold;
        }
        return employeeNum_UL;
    }
};

class PriorityQueue : public ISorting {
public:
    virtual void sort(vector<string> list) override {
        for (auto& e : list) {
            pq_.push(e);
        }
    }

    virtual vector<string> getTopk(size_t k = 5) override {
        vector<string> result{};

        if (k == 0) { // Return ALL
            while (!pq_.empty()) {
                result.push_back(pq_.top());
                pq_.pop();
            }
            return result;
        }

        result.reserve(k);
        for (size_t i = 0; i < k && !pq_.empty(); ++i) {
            result.push_back(pq_.top());
            pq_.pop();
        }

        return result;
    }

    virtual vector<string> sort_partial(vector<string> list, size_t k = 5) override {
        vector<string> results;
        results.resize(list.size() < k ? list.size() : k);
        partial_sort_copy(list.begin(), list.end(), results.begin(), results.end(), cmp_less());
        return results;
    }

private:
    priority_queue<string, vector<string>, cmp_greater> pq_;
};
