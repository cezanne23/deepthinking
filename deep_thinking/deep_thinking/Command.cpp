#include <vector>
#include "Command.h"

using namespace std;

string AddCommand::runCmd(vector<string>& command) {
    // todo 별도 class 정의 필요
    EmployeeInfo employee{ command[ADD_CMD_EMPLOYEENUM_INFO_IDX],
        command[ADD_CMD_NAME_INFO_IDX],
        command[ADD_CMD_LEVEL_INFO_IDX],
        command[ADD_CMD_PHONENUM_INFO_IDX],
        command[ADD_CMD_BIRTHDAY_INFO_IDX],
        command[ADD_CMD_CERTI_INFO_IDX] };

    employeeDB->employeeList.insert(pair<string, EmployeeInfo>(command[ADD_CMD_EMPLOYEENUM_INFO_IDX], employee));
    return "";
};

string DeleteCommand::runCmd(vector<string>& command) {
    vector<string> searchResult = searchEngine.seachID(employeeDB->employeeList, command);
    vector<string> displayRecord;
    if (command[CMD_DISPLAY_RECORD] == "-p") {
        displayRecord = displayEmployeeInfo(searchResult, "DEL");
    }

    for (const auto& employeeNum : searchResult) {
        employeeDB->employeeList.erase(employeeNum);
    }

    if (displayRecord.size() > 0) return convertToString(displayRecord);
    if (searchResult.size()) return to_string(searchResult.size());
    return "DEL,NONE";
};

string ModifyCommand::runCmd(vector<string>& command) {
    return "ModifyCommand";
};

string SearchCommand::runCmd(vector<string>& command) {
    string result = "";
    vector<string> searchIdList;
    vector<EmployeeInfo> employeeInfoList;
    vector<EmployeeInfo> employeeInfoListTop5;
    vector<string> strList;

    searchIdList = searchEngine.searchID(command);

    if (searchIdList.size() == 0) {
        return result = "SCH,NONE";
    }

    if (command[SCH_CMD_PRINT_INFO_IDX] == "-p")
    {
        for (const string& employeeNum : searchIdList)
        {
            employeeInfoList.push_back(employeeDB->employeeList.find(employeeNum)->second);
        }

        priorityQueue.sort(employeeInfoList);

        employeeInfoListTop5 = priorityQueue.getTopk();

        for (const EmployeeInfo& employeeInfo : employeeInfoListTop5)
        {
            strList.push_back("SCH," + employeeInfo.getEmployeeNum() + "," + employeeInfo.getName() + "," + employeeInfo.getLevel()
                + "," + employeeInfo.getPhoneNum() + "," + employeeInfo.getBirthDate() + "," + employeeInfo.getCerti());
        }
        result = convertToString(strList);
    }
    else if (command[SCH_CMD_PRINT_INFO_IDX] == " ") {
        result = ("SCH," + to_string(searchIdList.size()));
    }

    return result;
};
