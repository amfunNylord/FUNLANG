#include <fstream>
#include <iostream>

#include "FUNLanguageParser.h"

const std::string inputFileName = "input_code_test.txt";

int main()
{
	std::ifstream inputFile(inputFileName);

	std::string code, tempStr;

	while (inputFile >> tempStr)
	{
		code += tempStr;
	}

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