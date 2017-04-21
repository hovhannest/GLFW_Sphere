#pragma once


class IReusable
{
public:
	IReusable() {}
	virtual ~IReusable() {}

public:
	virtual void Init() = 0;
	virtual void Release() = 0;
};