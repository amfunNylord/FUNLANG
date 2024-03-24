#pragma once
#include <iostream>

const std::string IF_TERMINAL = "IF(";
const std::string THEN_TERMINAL = "THEN";
const std::string ELSE_TERMINAL = "ELSE";
const std::string FI_TERMINAL = "FI";

bool ParseIf(std::string& str)
{
	if (str.substr(0, IF_TERMINAL.length()) != IF_TERMINAL)
	{
		return false;
	}

	str.erase(0, IF_TERMINAL.length());

	size_t positionThen = str.find(THEN_TERMINAL);
	if (positionThen == std::string::npos) return false;

	if (!Expr(str.substr(0, positionThen)))
	{
		return false;
	}
	str.erase(0, positionThen);

	if (str.substr(0, THEN_TERMINAL.length()) != THEN_TERMINAL)
	{
		return false;
	}
	str.erase(0, THEN_TERMINAL.length());

	//что найдется первым else или fi
	size_t positionFi = str.find(FI_TERMINAL);
	size_t positionElse = str.find(ELSE_TERMINAL);

	if (positionFi != std::string::npos)
	{
		if (positionElse != std::string::npos && positionFi > positionElse)
		{
			if (!ParseSt(str.substr(0, positionElse))) // что в then
			{
				return false;
			}
			str.erase(0, positionElse);//st
			str.erase(0, ELSE_TERMINAL.length()); // удаляем else
			positionFi = str.find(FI_TERMINAL); // обновляем позицию потому что мы удаляли до этого
			if (!ParseSt(str.substr(0, positionFi)))
			{
				return false;
			}
			str.erase(0, positionFi); // st в else
			str.erase(0, FI_TERMINAL.length());
		}
		else // если нет else
		{
			if (!ParseSt(str.substr(0, positionFi)))
			{
				return false;
			}
			str.erase(0, positionFi);
			str.erase(0, FI_TERMINAL.length());
		}
	}
	else//если нет fi
	{
		return false;
	}

	return true;
}