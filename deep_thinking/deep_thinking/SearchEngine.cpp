
#include "SearchEngine.h"

vector<string> SearchEngineCore::seachID(const map<string, EmployeeInfo>& employeeInfo,
	const vector<string>& parsedCmds) {
	string serchOptionStr = parsedCmds[SEARCH_OPTION_IDX];
	vector<string> result = searchPolicyList[serchOptionStr]->search(employeeInfo, parsedCmds);

	return result;
}

template <typename T1>
vector<EmployeeInfo> search(const multimap<T1, EmployeeInfo> database, const int condition) {

#if 0
	if constexpr (std::is_same_v<T1, int >) {
		cout << "database type is  multimap<int, EmployeeInfo>\n";
	}
#endif
	vector<EmployeeInfo> ret;

	return ret;
}