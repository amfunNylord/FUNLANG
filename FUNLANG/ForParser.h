#pragma once
#include <iostream>
const std::string FOR_TERMINAL = "FOR";
const std::string ASSIGNMENT_TERMINAL = ":=";
const std::string TO_TERMINAL = "TO";
const std::string DO_TERMINAL = "DO";
const std::string ENDFOR_TERMINAL = "ENDFOR";

void DeleteSpaces(std::string& line)
{
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
}

bool FORParse(std::string& code)
{
	if (code.substr(0, 3) != FOR_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + FOR_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	code.erase(0, 3);
	if (!IDENTParse(code))
	{
		std::cout << "Syntax error: expected \'identifier\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (code.substr(0, 2) != ASSIGNMENT_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + ASSIGNMENT_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	code.erase(0, 2);
	if (!EXPRParse(code))
	{
		std::cout << "Syntax error: expected \'simple expression\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (code.substr(0, 2) != TO_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + TO_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	code.erase(0, 2);
	if (!EXPRParse(code))
	{
		std::cout << "Syntax error: expected \'simple expression\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (code.substr(0, 2) != DO_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + DO_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	code.erase(0, 2);
	if (!STParse(code))
	{
		std::cout << "Syntax error: expected \'statement\', line: pos:" << std::endl; // from lexer
		return false;
	}
	if (code.substr(0, 6) != ENDFOR_TERMINAL)
	{
		std::cout << "Syntax error: expected \'" + ENDFOR_TERMINAL + "\', line: pos:" << std::endl; // from lexer
		return false;
	}
	code.erase(0, 6);

	return true;
}