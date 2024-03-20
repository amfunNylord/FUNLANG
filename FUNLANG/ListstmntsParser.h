#pragma once

#include <string>

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
	if (!EMPTYParse(code))
	{
		return false;
	}
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