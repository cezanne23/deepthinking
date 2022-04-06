#include "SearchEngine.h"

vector<string> SearchEngineCore::searchID(const map<string, EmployeeInfo>& employeeInfo,
    const vector<string>& parsedCmds) {
    string serchOptionStr = parsedCmds[SEARCH_OPTION_IDX];
    vector<string> result = searchPolicyList[serchOptionStr]->search(employeeInfo, parsedCmds);

    return result;
}

