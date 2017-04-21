#pragma once


class IDrawable
{
public:
	IDrawable() {}
	virtual ~IDrawable() {}

public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};