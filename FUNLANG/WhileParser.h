#pragma once
#include <iostream>
#include "EXPRParse.h"

const std::string WHILE_START_TERMINAL = "WHILE";
const std::string WHILE_END_TERMINAL = "ENDWHILE";

bool STParse(std::string& code);

bool WHILEParse(std::string& code)
{
	if (code.substr(0, 5) != WHILE_START_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + WHILE_START_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	code.erase(0, 5);
	if (!EXPRParse(code))
	{
		std::cout << "Syntax error: expected \'identifier\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (code.substr(0, 2) != "DO")
	{
		return false;
	}
	code.erase(0, 2);
	if (!STParse(code))
	{
		std::cout << "Syntax error: expected \'statement\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (code.substr(0, 8) != WHILE_END_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + WHILE_END_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	code.erase(0, 8);
	return true;
}