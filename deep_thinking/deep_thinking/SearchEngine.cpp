
#include "SearchEngine.h"

vector<string> SearchEngine::seachID(const map<string, EmployeeInfo>& employeeInfo,
	const string condition) {
	vector<string> parsedCmds = parSer.split(condition, CMD_DISC);
	string serchOptionStr = parsedCmds[SEARCH_OPTION_IDX];
	vector<string> result = searchPolicyList[serchOptionStr]->search(employeeInfo, parsedCmds);

	return result;
}
