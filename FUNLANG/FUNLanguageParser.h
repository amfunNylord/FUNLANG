#pragma once
#include <string>

#include "ListstmntsParser.h"
#include "DCLSParser.h"

const std::string FUN_TERMINAL = "FUN";
const std::string MAIN_TERMINAL = "MAIN";
const std::string NUF_TERMINAL = "NUF";
const std::string BEGIN_TERMINAL = "BEGIN";
const std::string END_TERMINAL = "END";

bool FUNLanguageParse(std::string code)
{
	if (code.substr(0, 3) != FUN_TERMINAL)
	{
		// print error
		return false;
	}
	code.erase(0, 3);
	
	if (code.substr(0, 4) != MAIN_TERMINAL)
	{
		// print error
		return false;
	}
	code.erase(0, 4);

	if (code.substr(0, 1) != "\n")
	{
		return false;
	}
	code.erase(0, 1);

	if (!DCLSParse(code))
	{
		// print error
		return false;
	}
	if (code.substr(0, 5) != BEGIN_TERMINAL)
	{
		//print error
		return false;
	}
	code.erase(0, 5);
	if (code.substr(0, 1) != "\n")
	{
		return false;
	}
	code.erase(0, 1);
	if (!LISTSTMNTSParse(code))
	{
		// print error
		return false;
	}
	if (code.substr(0, 3) != END_TERMINAL)
	{
		// print error
		return false;
	}
	code.erase(0, 3);
	if (code.substr(0, 1) != "\n")
	{
		return false;
	}
	code.erase(0, 1);
	if (code.substr(0, 3) != NUF_TERMINAL)
	{
		// print error
		return false;
	}
	code.erase(0, 3);
	if (code.substr(0, 1) != "\n")
	{
		return false;
	}
	code.erase(0, 1);

	if (code.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}