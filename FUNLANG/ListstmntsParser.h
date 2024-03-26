#pragma once

#include <string>
#include "WhileParser.h"
#include "ForParser.h"
#include "IFParser.h"
#include "ReadAndWriteParser.h"

bool LISTSTMNTSParse(std::string& code);

bool EMPTYParse(std::string& code)
{
	if (code[0] != ';')
	{
		return false;
	}
	code.erase(0, 1);
	if (code.substr(0, 1) != "\n")
	{
		return false;
	}
	code.erase(0, 1);
	return true;
}

bool STParse(std::string& code)
{
	if (code[0] == '{')
	{
		code.erase(0, 1);
		if (code.substr(0, 1) != "\n")
		{
			return false;
		}
		code.erase(0, 1);
		if (!LISTSTMNTSParse(code))
		{
			return false;
		}
		if (code[0] != '}')
		{
			return false;
		}
		code.erase(0, 1);
		if (code.substr(0, 1) != "\n")
		{
			return false;
		}
		code.erase(0, 1);
	}
	if (EMPTYParse(code))
	{
		return true;
	}
	else if (code.substr(0, 5) == WHILE_START_TERMINAL) // use const
	{
		if (!WHILEParse(code))
		{
			return false;
		}
	}
	else if (code.substr(0, 3) == FOR_TERMINAL) // use const
	{
		if (!FORParse(code))
		{
			return false;
		}
	}
	else if (code.substr(0, 2) == "IF") // use const
	{
		if (!IFParse(code))
		{
			return false;
		}
	}
	else if (code.substr(0, 4) == "READ") // use const
	{
		if (!READParse(code))
		{
			return false;
		}
	}
	else if (code.substr(0, 5) == "WRITE") // use const
	{
		if (!WRITEParse(code))
		{
			return false;
		}
	}
	//else if (!ASSIGNMENTParse(code)) // вывод ошибки если просто текст то это ошибка что ожидалось st, а если неправильно написан assignment другая ошибка надо вырулить
	//{
	//	return false;
	//}
	return true;
}

bool LISTSTMNTSParse(std::string& code)
{
	if (!STParse(code))
	{
		// error
		return false;
	}
	if (code.substr(0, 1) == "\n")
	{
		code.erase(0, 1);
		if (!LISTSTMNTSParse(code))
		{
			// error
			return false;
		}
	}
	return true;
}