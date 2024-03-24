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
const std::string NOT_TERMINAL = "NOT";
const float MAX_FLOAT = 3.40282e+38f;
const float MIN_FLOAT = -3.40282e+38f;
const size_t FLOAT_PRECISION = 7;
const double MAX_DOUBLE = 1.7976931348623157e+308;
const double MIN_DOUBLE = -1.7976931348623157e+308;
const size_t DOUBLE_PRECISION = 16;

bool FParse(std::string& code);
bool IDENTParse(std::string& code);

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

bool TERMParse(std::string& code)
{
	/*TERMParse(code); // ??
 	MULParse(code);*/
	if (!FParse(code))
	{
		return false;
	}
	return true;
}

bool SIMPLEEXPRParse(std::string& code)
{
	/*SIMPLEEXPRParse(code); // ??
	PLUSParse(code);*/
	if (!TERMParse(code))
	{
		return false;
	}
	return true;
}

bool INTParse(std::string& code)
{
	int i = 0;
	std::string value;
	while (isdigit(code[i]))
	{
		value += code[i++];
	}
	size_t valueLen = value.size();
	code.erase(0, valueLen);
	return valueLen != 0;
}

bool DOUBLEParse(std::string& code)
{
	int i = 0;
	std::string value;
	if (code[i] == '-')
	{
		value += '-';
		i++;
	}
	if (!isdigit(code[i]))
	{
		return false;
	}
	while (isdigit(code[i]))
	{
		value += code[i];
		i++;
	}
	if (std::stoi(value) > MAX_DOUBLE)
	{
		return false;
	}
	if (std::stoi(value) < MIN_DOUBLE)
	{
		return false;
	}
	if (code[i] != '.')
	{
		return false;
	}
	value += '.';
	i++;
	std::string afterDot;
	while (isdigit(code[i]))
	{
		afterDot += code[i];
		i++;
	}
	if (afterDot.size() > DOUBLE_PRECISION)
	{
		return false;
	}
	value += afterDot;
	code.erase(0, value.size());
	return true;
}

bool FLOATParse(std::string& code)
{
	int i = 0;
	std::string value;
	if (code[i] == '-')
	{
		value += '-';
		i++;
	}
	if (!isdigit(code[i]))
	{
		return false;
	}
	while (isdigit(code[i]))
	{
		value += code[i];
		i++;
	}
	if (std::stoi(value) > MAX_FLOAT)
	{
		return false;
	}
	if (std::stoi(value) < MIN_FLOAT)
	{
		return false;
	}
	if (code[i] != '.')
	{
		return false;
	}
	value += '.';
	i++;
	std::string afterDot;
	while (isdigit(code[i]))
	{
		afterDot += code[i];
		i++;
	}
	if (afterDot.size() > FLOAT_PRECISION)
	{
		return false;
	}
	value += afterDot;
	code.erase(0, value.size());
	return true;
}

bool NUMBParse(std::string& code)
{
	if (!INTParse(code) && !FLOATParse(code) && !DOUBLEParse(code))
	{
		return false;
	}
	return true;
}

bool FParse(std::string& code)
{
	if (IDENTParse(code))
	{
		return true;
	}
	if (NUMBParse(code))
	{
		return true;
	}
	if (code[0] == '-')
	{
		code.erase(0, 1);
		return FParse(code);
	}
	if (code[0] == '(')
	{
		code.erase(0, 1);
		if (!SIMPLEEXPRParse(code))
		{
			return false;
		}
		if (code[0] != ')')
		{
			return false;
		}
		code.erase(0, 1);
		return true;
	}
	if (code.substr(0, 3) == NOT_TERMINAL)
	{
		code.erase(0, 3);
		return FParse(code);
	}
	return false;
}

bool EXPRParse(std::string& code)
{
	// ??
	/*EXPRParse(code);
	RELATIONParse(code);*/
	if (!SIMPLEEXPRParse(code))
	{
		return false;
	}
	return true;
}