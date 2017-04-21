#pragma once

#include "GEEvent.h"
#include "Utils\GEConfig.h"

class IEventDelegate
{
public:
	IEventDelegate() {}
	~IEventDelegate() {}

public:
	virtual void OnEvent(CGEEvent* ev) {};

	void SendEvent(CGEEvent* ev, IEventDelegate* target);
	void SendEvent(uint32 evID, IEventDelegate* target);
};
