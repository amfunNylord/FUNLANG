#pragma once
#include <iostream>
const std::string WHILE_START_TERMINAL = "WHILE";
const std::string DO_TERMINAL = "DO";
const std::string WHILE_END_TERMINAL = "ENDWHILE";

bool PawrseWhile(std::string& str)
{
	if (str.substr(0, WHILE_START_TERMINAL.length()) != WHILE_START_TERMINAL)
	{
		return false;
	}
	str.erase(0, WHILE_START_TERMINAL.length());

	size_t positionDo = str.find(DO_TERMINAL);
	if (positionDo == std::string::npos)
	{
		return false;
	}
	if (!Expr(str.substr(0, positionDo)))
	{
		return false;
	}
	str.erase(0, positionDo);

	if (str.substr(0, DO_TERMINAL.length()) != DO_TERMINAL)
	{
		return false;
	}
	str.erase(0, DO_TERMINAL.length());

	size_t positionEndWhile = str.find(WHILE_END_TERMINAL);
	if (positionEndWhile == std::string::npos)
	{
		return false;
	}
	if (!ParseSt(str.substr(0, positionEndWhile)))
	{
		return false;
	}
	str.erase(0, positionEndWhile);

	if (str.substr(0, WHILE_END_TERMINAL.length()) != WHILE_END_TERMINAL)
	{
		return false;
	}
	str.erase(0, WHILE_END_TERMINAL.length());

	return true;
}