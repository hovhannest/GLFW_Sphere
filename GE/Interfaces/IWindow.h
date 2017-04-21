#pragma once

#include "IReusable.h"
#include "IDrawable.h"


class IWindow : 
	public IReusable,
	public IDrawable
{
public:
	IWindow() {}
	virtual ~IWindow() {}

public:
	virtual bool WindowShouldClose() = 0;
};