#pragma once
#include <string>

const char EQUAL = '=';
const char LESS = '<';
const char MORE = '>';
const std::string NOT_EQUAL = "<>";
const std::string LESS_EQUAL = "<=";
const std::string MORE_EQUAL = ">=";
const char PLUS = '+';
const std::string OR = "or";
const char MULTIPLY = '*';
const char DIVIDE = '/';
const std::string DIV = "DIV";
const std::string AND = "AND";
const std::string MOD = "MOD";

bool MULParse(std::string& code)
{
	if (code[0] == MULTIPLY || code[0] == DIVIDE)
	{
		code.erase(0, 1);
		return true;
	}
	std::string part = code.substr(0, 3);
	if (part == DIV || part == AND || part == MOD)
	{
		code.erase(0, 3);
		return true;
	}
	return false;
}

bool PLUSParse(std::string& code)
{
	if (code[0] == PLUS)
	{
		code.erase(0, 1);
		return true;
	}
	if (code.substr(0, 2) == OR)
	{
		code.erase(0, 2);
		return true;
	}
	return false;
}

bool RELATIONParse(std::string& code)
{
	if (code[0] == EQUAL || code[0] == LESS || code[0] == MORE)
	{
		code.erase(0, 1);
		return true;
	}
	if (code.substr(0, 2) == NOT_EQUAL || code.substr(0, 2) == LESS_EQUAL || code.substr(0, 2) == MORE_EQUAL)
	{
		code.erase(0, 2);
		return true;
	}
	return false;
}

bool EXPRParse(std::string& code)
{
	return true;
}