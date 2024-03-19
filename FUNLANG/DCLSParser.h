#pragma once

#include <string>
#include <set>

const std::string INT_TERMINAL = "int";
const std::string DOUBLE_TERMINAL = "double";
const std::string STRING_TERMINAL = "string";
const std::string CHAR_TERMINAL = "char";
const std::string FLOAT_TERMINAL = "float";
const std::string BOOL_TERMINAL = "bool";
const std::string CONST_TERMINAL = "CONST";
const std::string NOC_TERMINAL = "NOC";

const std::set<std::string> RESERVED_WORDS = { DOUBLE_TERMINAL, INT_TERMINAL, STRING_TERMINAL, CHAR_TERMINAL, FLOAT_TERMINAL, BOOL_TERMINAL, CONST_TERMINAL, NOC_TERMINAL };

bool TYPEParse(std::string& code)
{
	std::string terminal;
	if (code.substr(0, 3) == INT_TERMINAL)
	{
		terminal = INT_TERMINAL;
	}
	if (code.substr(0, 4) == CHAR_TERMINAL)
	{
		terminal = CHAR_TERMINAL;
	}
	if (code.substr(0, 4) == BOOL_TERMINAL)
	{
		terminal = BOOL_TERMINAL;
	}
	if (code.substr(0, 5) == FLOAT_TERMINAL)
	{
		terminal = FLOAT_TERMINAL;
	}
	if (code.substr(0, 6) == STRING_TERMINAL)
	{
		terminal = STRING_TERMINAL;
	}
	if (code.substr(0, 6) == DOUBLE_TERMINAL)
	{
		terminal = DOUBLE_TERMINAL;
	}

	if (terminal.empty())
	{
		//print error
		return false;
	}
	code.erase(0, terminal.size());
	return true;
}

bool IDENTParse(std::string& code)
{
	std::string identifier;
	int i = 0;
	while (isalpha(code[i]))
	{
		identifier += code[i++];
	}
	if (RESERVED_WORDS.contains(identifier))
	{
		//error
		return false;
	}
	code.erase(0, identifier.size());
	return true;
}

bool CONSTSECTIONParse(std::string& code)
{
	if (!IDENTParse(code))
	{
		//error
		return false;
	}
	if (code[0] != ':')
	{
		//error
		return false;
	}
	code.erase(0, 1);
	if (!TYPEParse(code))
	{
		//error
		return false;
	}
	if (code[0] != '=')
	{
		//error
		return false;
	}
	code.erase(0, 1);
	// ParseExpr
	return true;
}

bool CONSTSECTIONSParse(std::string& code)
{
	if (!CONSTSECTIONParse(code))
	{
		//error
		return false;
	}
	if (code[0] == ';')
	{
		code.erase(0, 1);
		if (code.substr(0, 1) != "\n")
		{
			return false;
		}
		code.erase(0, 1);
		if (!CONSTSECTIONSParse(code))
		{
			return false;
		}
	}

	return true;
	//if (!((CONSTSECTIONParse(code) && code[0] == ';' && CONSTSECTIONSParse(code)) || CONSTSECTIONParse(code)))
	//{
	//	//error
	//	return false;
	//}
	//return true;
}

bool CONSTParse(std::string& code)
{
	if (code.substr(0, 5) != CONST_TERMINAL)
	{
		//error
		return false;
	}
	code.erase(0, 5);
	if (code.substr(0, 1) != "\n")
	{
		return false;
	}
	code.erase(0, 1);
	if (!CONSTSECTIONSParse(code))
	{
		//error
		return false;
	}
	if (code.substr(0, 1) != "\n")
	{
		return false;
	}
	code.erase(0, 1);
	if (code.substr(0, 3) != NOC_TERMINAL)
	{
		//error
		return false;
	}
	code.erase(0, 3);
	if (code.substr(0, 1) != "\n")
	{
		return false;
	}
	code.erase(0, 1);
	return true;
}

bool VARParse(std::string& code)
{
	return true;
}

bool DCLSParse(std::string& code)
{
	// if (!((CONSTParse(code) && VARParse(code)) || VARParse(code)))
	//{
	//	// error
	//	return false;
	// }
	// return true;
	CONSTParse(code);
	if (!VARParse(code))
	{
		//error
		return false;
	}
	return true;
}