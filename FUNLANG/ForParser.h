#pragma once
#include <iostream>
const std::string FOR_TERMINAL = "FOR";
const std::string ASSIGNMENT_TERMINAL = ":=";
const std::string TO_TERMINAL = "TO";
const std::string DO_TERMINAL = "DO";
const std::string ROF_TERMINAL = "ROF";

bool ParseFOR(std::string& str)
{
	if (str.substr(0, FOR_TERMINAL.length()) != FOR_TERMINAL)
	{
		return false;
	}
	str.erase(0, FOR_TERMINAL.length());

	size_t positionTo = str.find(TO_TERMINAL);
	if (positionTo == std::string::npos)
	{
		return false;
	}

	if (!Expr(0, positionTo))
	{
		return false;
	}
	str.erase(0, positionTo);

	if (str.substr(0, TO_TERMINAL.length()) != TO_TERMINAL)
	{
		return false;
	}
	str.erase(0, TO_TERMINAL.length());

	size_t positionDo = str.find(DO_TERMINAL);
	if (positionDo == std::string::npos)
	{
		return false;
	}

	//хз тут что
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

	size_t positionRof = str.find(ROF_TERMINAL);
	if (positionRof == std::string::npos)
	{
		return false;
	}

	if (!ParseSt(str.substr(0, positionRof)))
	{
		return false;
	}
	str.erase(0, positionRof);

	if (str.substr(0, ROF_TERMINAL.length()) != ROF_TERMINAL)
	{
		return false;
	}
	str.erase(0, ROF_TERMINAL.length());
	return true;

}