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
    if (searchResult.size()) return "DEL,"+ to_string(searchResult.size());
    return "DEL,NONE";
};

string ModifyCommand::runCmd(vector<string>& command) {
	vector<string> searchResult = searchEngine.seachID(employeeDB->employeeList, command);
	vector<string> displayRecord;

    if (command[CMD_DISPLAY_RECORD] == "-p") {
        displayRecord = displayEmployeeInfo(searchResult, "MOD");
    }

	for (const auto& employeeNum : searchResult) {
		// todo refactoring
		if (command[MOD_TARGET_KEY_IDX] == EMPLOYEENUM) {
			// requirement: should not change id
            // employeeDB->employeeList[employeeNum].setEmployeeNum(command[MOD_TARGET_VALUE_IDX]);
		}
		else if (command[MOD_TARGET_KEY_IDX] == BIRTHDAY) {
			employeeDB->employeeList[employeeNum].setBirthDate(command[MOD_TARGET_VALUE_IDX]);
		}
		else if (command[MOD_TARGET_KEY_IDX] == NAME) {
			employeeDB->employeeList[employeeNum].setName(command[MOD_TARGET_VALUE_IDX]);
		}
		else if (command[MOD_TARGET_KEY_IDX] == CERTI) {
			employeeDB->employeeList[employeeNum].setCerti(command[MOD_TARGET_VALUE_IDX]);
		}
		else if (command[MOD_TARGET_KEY_IDX] == CL) {
			employeeDB->employeeList[employeeNum].setLevel(command[MOD_TARGET_VALUE_IDX]);
		}
		else if (command[MOD_TARGET_KEY_IDX] == PHONENUM) {
			employeeDB->employeeList[employeeNum].setPhoneNum(command[MOD_TARGET_VALUE_IDX]);
		}
		else { // exception
			throw;
		}
	}

	if (displayRecord.size() > 0)
		return convertToString(displayRecord);
	if (searchResult.size() > 0 )
		return string("MOD,") + to_string(searchResult.size());
	return "MOD,NONE";
};

string SearchCommand::runCmd(vector<string>& command) {
    vector<string> searchResult = searchEngine.seachID(employeeDB->employeeList, command);
    vector<string> displayRecord;

    if (searchResult.size() == 0) return "SCH,NONE";

    if (command[CMD_DISPLAY_RECORD] == "-p") {
        displayRecord = displayEmployeeInfo(searchResult, "SCH");
        return convertToString(displayRecord);
    }
    return "SCH," + to_string(searchResult.size());
};
