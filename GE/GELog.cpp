#include "GELog.h"

#include <iostream>

void CGELog::Fatal(int code, const char* msg)
{
	std::cerr << "Fatal Error: " << code << std::endl;
	std::cerr << msg << std::endl;
	exit(code);
}

void CGELog::Trace(const char* msg)
{
	std::cout << "Trace: " << msg << std::endl;
}

void CGELog::Assert(bool isTrue, const char* msg)
{
	if (!isTrue)
	{
		std::cout << "Assert: " << msg << std::endl;
	}
}
