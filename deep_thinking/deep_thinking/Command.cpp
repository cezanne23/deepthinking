#include <vector>
#include "Command.h"

using namespace std;

bool EmployeeNumCmp(const string& A, const string& B)
{
    unsigned long long int aUL = stoi(A);
    unsigned long long int bUL = stoi(B);

    if (aUL < 69000000) {
        aUL += 100000000;
    }

    return (aUL < bUL);
}

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
    return "DeleteCommand";
};

string ModifyCommand::runCmd(vector<string>& command) {
    return "ModifyCommand";
};

string SearchCommand::runCmd(vector<string>& command) {
    string result = "";
    vector<string> searchIdList;

    searchIdList = searchEngine.searchID(command);

    if (searchIdList.size() == 0) {
        return result = "SCH,NONE";
    }

    searchIdList = sortForEmployNum(searchIdList);

    if (command[SCH_CMD_PRINT_INFO_IDX] == "-p")
    {
        EmployeeInfo employeeInfo;
        for (const string& employeeNum : searchIdList)
        {
            employeeInfo = employeeDB->employeeList.find(employeeNum)->second;
            result += ("SCH," + employeeInfo.getEmployeeNum() + "," + employeeInfo.getName() + "," + employeeInfo.getLevel()
                + "," + employeeInfo.getPhoneNum() + "," + employeeInfo.getBirthDate() + "," + employeeInfo.getCerti());
        }
    }
    else if (command[SCH_CMD_PRINT_INFO_IDX] == " ") {
        result = ("SCH," + to_string(searchIdList.size()));
    }

    return result;
};
