#include <iostream>
#include "EmployeeInfoManager.h"

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;

    EmployeeInfoManager employeeInfoManager;
    employeeInfoManager.Run(argv[1], argv[2]);

    return 0;
}