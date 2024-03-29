#pragma once
#include <iostream>
#include "DCLSParser.h"

const std::string SYNTAX_ERROR_READ = "Syntax error: expected 'READ(', line: pos:";
const std::string SYNTAX_ERROR_WRITE = "Syntax error: expected 'WRITE(', line: pos:";
const std::string SYNTAX_ERROR_MISSING_COMMA = "Syntax error: expected ',' after identifier, line: pos:";
const std::string SYNTAX_ERROR_MISSING_QUOTE = "Syntax error: expected closing '\"' for string, line: pos:";
const std::string SYNTAX_ERROR_UNEXPECTED_SYMBOL = "Syntax error: unexpected symbol in identifier, line: pos:";

const std::string READ_TERMINAL = "READ(";
const std::string WRITE_TERMINAL = "WRITE(";

void PrintSyntaxError(const std::string& errorMessage, size_t position)
{
	std::cout << errorMessage << position << std::endl;
}

bool READParse(std::string& str)
{
	size_t index = 0;
	if (str.substr(0, READ_TERMINAL.size()) != READ_TERMINAL)
	{
		PrintSyntaxError(SYNTAX_ERROR_READ, 0);
		return false;
	}

	str.erase(0, READ_TERMINAL.size());
	index += READ_TERMINAL.size();

	size_t findSymbol = 0;
	bool firstIdentifier = true;

	while (findSymbol != std::string::npos)
	{
		if (!firstIdentifier)
		{
			if (str.substr(0, 1) != ",")
			{
				PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
				return false;
			}
			str.erase(0, 1);
			index++;
		}

		findSymbol = str.find(",");
		// �������� �� �� ����� ������� , ���� ������ )
		if (findSymbol != std::string::npos)
		{
			size_t positionBracket = str.find(")");
			if (positionBracket < findSymbol)
			{
				findSymbol = std::string::npos;
			}
		}



		if (findSymbol == std::string::npos)
		{
			if (str == ")")
			{
				PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
				return false;
			}

			findSymbol = str.find(")");

			if (findSymbol == std::string::npos)
			{
				PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
				return false;
			}
			else
			{
				std::string tempIdentifier = str.substr(0, findSymbol);
				str.erase(0, findSymbol);
				if (!IDENTParse(tempIdentifier)) 
				{
					PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
					return false;
				}
				str.erase(0, 1);//�������)
				if (str[0] != ';')
				{
					return false;
				}
				str.erase(0, 1); //������� ;
				break;
			}
		}

		std::string tempIdentifier = str.substr(0, findSymbol);
		str.erase(0, findSymbol);
		if (!IDENTParse(tempIdentifier))
		{
			PrintSyntaxError(SYNTAX_ERROR_READ, index + findSymbol);
			return false;
		}

		index += findSymbol;

		firstIdentifier = false;
	}

	return true;
}

bool WRITEParse(std::string& str)
{
	size_t index = 0;
	if (str.substr(0, WRITE_TERMINAL.size()) != WRITE_TERMINAL)
	{
		PrintSyntaxError(SYNTAX_ERROR_WRITE, 0);
		return false;
	}

	str.erase(0, WRITE_TERMINAL.size());
	index += WRITE_TERMINAL.size();

	size_t findSymbol = 0;
	bool firstIdentifier = true;

	while (findSymbol != std::string::npos)
	{
		if (!firstIdentifier)
		{
			if (str.substr(0, 1) != ",")
			{
				PrintSyntaxError(SYNTAX_ERROR_MISSING_COMMA, index + findSymbol);
				return false;
			}
			str.erase(0, 1);
			index++;
		}

		if (str.substr(0, 1) == "\"")
		{
			size_t closingQuote = str.find("\"", 1);
			if (closingQuote == std::string::npos)
			{
				PrintSyntaxError(SYNTAX_ERROR_MISSING_QUOTE, index + findSymbol);
				return false;
			}
			str.erase(0, closingQuote + 1);
			index += closingQuote + 1;
			firstIdentifier = false;
			continue;
		}

		findSymbol = str.find(",");
		// �������� �� �� ����� ������� , ���� ������ )
		if (findSymbol != std::string::npos)
		{
			size_t positionBracket = str.find(")");
			if (positionBracket < findSymbol)
			{
				findSymbol = std::string::npos;
			}
		}

		if (findSymbol == std::string::npos)
		{
			if (str == ")")
			{
				PrintSyntaxError(SYNTAX_ERROR_MISSING_COMMA, index + findSymbol);
				return false;
			}

			findSymbol = str.find(")");

			if (findSymbol == std::string::npos)
			{
				PrintSyntaxError(SYNTAX_ERROR_MISSING_COMMA, index + findSymbol);
				return false;
			}
			else
			{
				std::string tempIdentifier = str.substr(0, findSymbol);
				str.erase(0, findSymbol);
				if (!IDENTParse(tempIdentifier))
				{
					PrintSyntaxError(SYNTAX_ERROR_UNEXPECTED_SYMBOL, index + findSymbol);
					return false;
				}

				str.erase(0, 1); // �������)
				if (str[0] != ';')
				{
					return false;
				}
				str.erase(0, 1); // ������� ;
				break;
			}
		}

		std::string tempIdentifier = str.substr(0, findSymbol);
		str.erase(0, findSymbol);
		if (!IDENTParse(tempIdentifier))
		{
			PrintSyntaxError(SYNTAX_ERROR_UNEXPECTED_SYMBOL, index + findSymbol);
			return false;
		}


		index += findSymbol;

		firstIdentifier = false;
	}

	return true;
}