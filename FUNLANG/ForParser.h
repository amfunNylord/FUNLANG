#pragma once
#include <iostream>
const std::string FOR_TERMINAL = "FOR";
const std::string ASSIGNMENT_TERMINAL = ":=";
const std::string TO_TERMINAL = "TO";
const std::string DO_TERMINAL = "DO";
const std::string ENDFOR_TERMINAL = "ENDFOR";
#include "ExpressionParser.h"
#include "ListstmntsParser.h"

bool FORParse(std::string& str)
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

	//if (!RuleExpr(str.substr(0, positionTo)))
	//{
	//	return false;
	//}
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


	if (!RuleExpr(str.substr(0, positionDo)))
	{
		return false;
	}
	str.erase(0, positionDo);

	if (str.substr(0, DO_TERMINAL.length()) != DO_TERMINAL)
	{
		return false;
	}
	str.erase(0, DO_TERMINAL.length());

	size_t positionRof = str.find(ENDFOR_TERMINAL);
	if (positionRof == std::string::npos)
	{
		return false;
	}
	std::string copyStr = str.substr(0, positionRof);
	if (!STParse(copyStr))
	{
		return false;
	}
	str.erase(0, positionRof);

	if (str.substr(0, ENDFOR_TERMINAL.length()) != ENDFOR_TERMINAL)
	{
		return false;
	}
	str.erase(0, ENDFOR_TERMINAL.length());
	return true;
}