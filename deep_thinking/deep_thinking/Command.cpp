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
    vector<string> searchList = searchEngine.seachID(employeeDB->employeeList, command);
    for (const auto& employeeNum : searchList) {
        employeeDB->employeeList.erase(employeeNum);
    }
    //for (const auto& item : employeeDB->employeeList) {
    //    cout << item.first << " " << item.second << endl;
    //}
    return to_string(searchList.size());
};

string ModifyCommand::runCmd(vector<string>& command) {
    return "ModifyCommand";
};

string SearchCommand::runCmd(vector<string>& command) {
    return "SearchCommand";
};
