#include <fstream>
#include <iostream>

#include "FUNLanguageParser.h"

const std::string inputFileName = "input_code_test.txt";

void DeleteSpacesAndTabs(std::string& line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	line.erase(remove(line.begin(), line.end(), '\t'), line.end());
}

int main()
{
	std::ifstream inputFile(inputFileName);

	std::string code, tempStr;

	while (getline(inputFile, tempStr))
	{
		code += tempStr;
		code += '\n';
	}

	DeleteSpacesAndTabs(code);

	if (!FUNLanguageParse(code))
	{
		std::cout << "ERROR" << std::endl;
	}
	else
	{
		std::cout << "SUCCESS" << std::endl;
	}

	return 0;
}