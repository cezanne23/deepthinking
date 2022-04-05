#include <vector>
#include "Command.h"
#include "OptionParser.h"

using namespace std;

string AddCommand::runCmd(vector<string>& command) {
    // todo º°µµ class Á¤ÀÇ ÇÊ¿ä
    EmployeeInfo employee{ command[ADD_CMD_EMPLOYEENUM_INFO_IDX],
        command[ADD_CMD_NAME_INFO_IDX],
        command[ADD_CMD_LEVEL_INFO_IDX],
        command[ADD_CMD_PHONENUM_INFO_IDX],
        command[ADD_CMD_BIRTHDAY_INFO_IDX],
        command[ADD_CMD_CERTI_INFO_IDX] };

    employeeDB->employeeList.insert(pair<string, EmployeeInfo>(command[ADD_CMD_EMPLOYEENUM_INFO_IDX], employee));

    employeeDB->fullNameMap.insert(pair<string, string>(employee.getName(), employee.getEmployeeNum()));
    employeeDB->firstNameMap.insert(pair<string, string>(employee.getFirstName(), employee.getEmployeeNum()));
    employeeDB->lastNameMap.insert(pair<string, string>(employee.getLastName(), employee.getEmployeeNum()));
    employeeDB->levelMap.insert(pair<string, string>(employee.getLevel(), employee.getEmployeeNum()));
    employeeDB->phoneNumMap.insert(pair<string, string>(employee.getPhoneNum(), employee.getEmployeeNum()));
    employeeDB->phoneMidNumMap.insert(pair<string, string>(employee.getPhoneMidNum(), employee.getEmployeeNum()));
    employeeDB->phoneLastNumMap.insert(pair<string, string>(employee.getPhoneLastNum(), employee.getEmployeeNum()));
    employeeDB->birthDateMap.insert(pair<string, string>(employee.getBirthDate(), employee.getEmployeeNum()));
    employeeDB->birthYearMap.insert(pair<string, string>(employee.getBirthYear(), employee.getEmployeeNum()));
    employeeDB->birthMonthMap.insert(pair<string, string>(employee.getBirthMonth(), employee.getEmployeeNum()));
    employeeDB->birthDayMap.insert(pair<string, string>(employee.getBirthDay(), employee.getEmployeeNum()));
    employeeDB->certiMap.insert(pair<string, string>(employee.getCerti(), employee.getEmployeeNum()));

    return "";
};

void deleteMultiMapDB(EmployeeDB* employeeDB, OptionType optionType, const EmployeeInfo& employee)
{
    if (nullptr == employeeDB) { return; }

    auto deleteOp = [](multimap<string, string>& map, const string key, const string value)->void {
        for (auto iter = map.lower_bound(key); iter != map.upper_bound(key); ++iter) {
            if (value == iter->second) {
                map.erase(iter);
                return;
            }
        }
    };

    switch (optionType) {
    case OptionType::FULL_NAME:
    case OptionType::FIRST_NAME:
    case OptionType::LAST_NAME:
        deleteOp(employeeDB->fullNameMap, employee.getName(), employee.getEmployeeNum());
        deleteOp(employeeDB->firstNameMap, employee.getFirstName(), employee.getEmployeeNum());
        deleteOp(employeeDB->lastNameMap, employee.getLastName(), employee.getEmployeeNum());
        break;
    case OptionType::PHONE_NUM:
    case OptionType::MID_PHONE_NUM:
    case OptionType::LAST_PHONE_NUM:
        deleteOp(employeeDB->phoneNumMap, employee.getPhoneNum(), employee.getEmployeeNum());
        deleteOp(employeeDB->phoneMidNumMap, employee.getPhoneMidNum(), employee.getEmployeeNum());
        deleteOp(employeeDB->phoneLastNumMap, employee.getPhoneLastNum(), employee.getEmployeeNum());
        break;
    case OptionType::DATE:
    case OptionType::YEAR:
    case OptionType::MONTH:
    case OptionType::DAY:
        deleteOp(employeeDB->birthDateMap, employee.getBirthDate(), employee.getEmployeeNum());
        deleteOp(employeeDB->birthYearMap, employee.getBirthYear(), employee.getEmployeeNum());
        deleteOp(employeeDB->birthMonthMap, employee.getBirthMonth(), employee.getEmployeeNum());
        deleteOp(employeeDB->birthDayMap, employee.getBirthDay(), employee.getEmployeeNum());
        break;
    case OptionType::CERTI:
        deleteOp(employeeDB->certiMap, employee.getCerti(), employee.getEmployeeNum());
        break;
    case OptionType::LEVEL:
        deleteOp(employeeDB->levelMap, employee.getLevel(), employee.getEmployeeNum());
        break;
    }
}

string DeleteCommand::runCmd(vector<string>& command) {
    vector<string> searchResult = searchEngine.seachID(employeeDB->employeeList, command);

    if (searchResult.size() == 0) return "DEL,NONE";

    vector<string> displayRecord;
    if (command[CMD_DISPLAY_RECORD] == "-p") {
        displayRecord = displayEmployeeInfo(searchResult, "DEL");
    }

    OptionParser optionParser{};
    OptionType optionType = optionParser.getOptionType(command);

    for (const auto& employeeNum : searchResult) {
        EmployeeInfo employee = employeeDB->employeeList[employeeNum];
        employeeDB->employeeList.erase(employeeNum);
        deleteMultiMapDB(employeeDB, optionType, employee);
    }

    if (displayRecord.size() > 0) return convertToString(displayRecord);
    return "DEL," + to_string(searchResult.size());
};

string ModifyCommand::runCmd(vector<string>& command) {
    vector<string> searchResult = searchEngine.seachID(employeeDB->employeeList, command);
    vector<string> displayRecord;

	if (command[CMD_DISPLAY_RECORD] == "-p") {
		displayRecord = displayEmployeeInfo(searchResult, "MOD");
	}
	string update_key = command[MOD_TARGET_KEY_IDX];
	MODUpdate* update = updateList[update_key];
	for (const auto& employeeNum : searchResult) {
		update->update(employeeDB->employeeList[employeeNum], command[MOD_TARGET_VALUE_IDX]);
	}

	if (displayRecord.size() > 0)
		return convertToString(displayRecord);
	if (searchResult.size() > 0)
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
