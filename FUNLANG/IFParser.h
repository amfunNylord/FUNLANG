#pragma once
#include <iostream>

const std::string IF_TERMINAL = "IF(";
const std::string THEN_TERMINAL = "THEN";
const std::string ELSE_TERMINAL = "ELSE";
const std::string FI_TERMINAL = "FI";

bool IFParse(std::string& str)
{
	if (str.substr(0, IF_TERMINAL.length()) != IF_TERMINAL)
	{
		return false;
	}

	str.erase(0, IF_TERMINAL.length());

	size_t positionThen = str.find(THEN_TERMINAL);
	if (positionThen == std::string::npos) return false;

	std::string code = str.substr(0, positionThen);
	if (!EXPRParse(code))
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
			code = str.substr(0, positionElse);
			if (!STParse(code)) // что в then
			{
				return false;
			}
			str.erase(0, positionElse);//st
			str.erase(0, ELSE_TERMINAL.length()); // удаляем else
			positionFi = str.find(FI_TERMINAL); // обновляем позицию потому что мы удаляли до этого
			code = str.substr(0, positionFi);
			if (!STParse(code))
			{
				return false;
			}
			str.erase(0, positionFi); // st в else
			str.erase(0, FI_TERMINAL.length());
		}
		else // если нет else
		{
			code = str.substr(0, positionFi);
			if (!STParse(code))
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