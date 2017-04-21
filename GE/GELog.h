#pragma once

#include "Utils/Singleton.h"

#define GELOG CGELog::GetInstance()
 
class CGELog : public Singleton<CGELog>
{
public:
	void Fatal(int code, const char* msg);
	void Trace(const char* msg);

	void Assert(bool isTrue, const char* msg);
};

