#pragma once

#include <iostream>
#include <vector>
#include <queue>

#include "EmployeeInfo.h"

using namespace std;

class ISorting {
public:
	virtual void sort(vector<EmployeeInfo> list) = 0;
	virtual vector<EmployeeInfo> getTopk(size_t k = 5) = 0;
};

class PriorityQueue : public ISorting{
public:
	virtual void sort(vector<EmployeeInfo> list) override {
		for (auto& e : list) {
			pq_.push(e);
		}
	}

	virtual vector<EmployeeInfo> getTopk(size_t k = 5) override {
		vector<EmployeeInfo> result{};

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

private:
	priority_queue<EmployeeInfo, vector<EmployeeInfo>, greater<EmployeeInfo>> pq_;
};
