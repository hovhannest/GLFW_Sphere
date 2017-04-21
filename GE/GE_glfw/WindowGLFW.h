#pragma once

#include "..\Interfaces\IWindow.h"

class GLFWwindow;
class CGEApp;

class CWindowGLFW : 
	public IWindow
{
public:
	CWindowGLFW(CGEApp* theApp);
	~CWindowGLFW();

public:
	virtual void Init();
	virtual void Release();

	virtual void Update(float dt);
	virtual void Render();

	virtual bool WindowShouldClose();

	void WaitEventsTimeout(float dt);

private:
	GLFWwindow* m_Window;
	CGEApp*		m_App;
};