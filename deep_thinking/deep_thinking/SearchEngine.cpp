
#include "SearchEngine.h"

vector<int> SearchEngine::seachID(const map<int, EmployeeInfo>& employeeInfo,
	const string condition) {
	vector<string> parsedCmds = parSer.split(condition, CMD_DISC);
	string serchOptionStr = parsedCmds[SEARCH_OPTION_IDX];
	vector<int> result = searchPolicyList[serchOptionStr]->search(employeeInfo, parsedCmds);

	return result;
}
