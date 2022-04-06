#include <iostream>
#include "EmployeeInfoManager.h"

using namespace std;

void printUsage() {
	cout << "deep_thining <input.txt> <output.txt> " << endl;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printUsage();
		return 0;
	}

	EmployeeInfoManager employeeInfoManager;
	employeeInfoManager.Run(argv[1], argv[2]);

	return 0;
}