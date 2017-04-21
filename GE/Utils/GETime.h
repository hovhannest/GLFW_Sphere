#pragma once

#include "GEConfig.h"

#include "Singleton.h"

class CGETime : public Singleton<CGETime>
{
public:
	int64 GetTimeNow();
	
	void Sleep(int64 milliseconds);
};