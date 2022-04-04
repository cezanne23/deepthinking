#include <vector>
#include "Command.h"

using namespace std;



string AddCommand::runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) {
    // todo 별도 class 정의 필요
    EmployeeInfo employee{ command[ADD_CMD_EMPLOYEENUM_INFO_IDX],
        command[ADD_CMD_NAME_INFO_IDX],
        command[ADD_CMD_LEVEL_INFO_IDX],
        command[ADD_CMD_PHONENUM_INFO_IDX],
        command[ADD_CMD_BIRTHDAY_INFO_IDX],
        command[ADD_CMD_CERTI_INFO_IDX] };

    employeeInfo.insert(pair<string, EmployeeInfo>(command[ADD_CMD_EMPLOYEENUM_INFO_IDX], employee));
    return "";
};

string DeleteCommand::runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) {


    return "DeleteCommand";
};

string ModifyCommand::runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) {
    return "ModifyCommand";
};

string SearchCommand::runCmd(map<string, EmployeeInfo>& employeeInfo, vector<string>& command) {
    // vector<string> result = searchEngine.seachID(employeeInfo, command);
    
    return "SearchCommand";
};
