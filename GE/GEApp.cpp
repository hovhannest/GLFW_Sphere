
#include "GEApp.h"

#include "Utils/GETime.h"
#include "GE_glfw/WindowGLFW.h"

#include <iostream>
#include "../Sphere.h"
#include "../common/shader.hpp"
#include <vector>
#include "../TriangleA.h"
#include "../CubeA.h"

CGEApp::CGEApp():
	m_Window(NULL),
	m_AppTsartTime(0),
	m_Frames(0),
	m_EnableRender(true),
	m_EnableUpdate(true),
	m_LastUpdateResult(true),
	m_EventMinDt(0.0)
{

}

CGEApp::~CGEApp()
{

}

FORCENOINLINE void CGEApp::SetEventMinDt(float val)
{
	m_EventMinDt = val;

#ifdef GE_GLFW
	((CWindowGLFW*)m_Window)->WaitEventsTimeout(m_EventMinDt);
#endif
}

void CGEApp::Init()
{
	m_AppTsartTime = CGETime::GetInstance()->GetTimeNow();
	m_Frames = 0;

	m_EnableRender = true;
	m_EnableUpdate = true;
	m_LastUpdateResult = true;

#ifdef GE_GLFW
	CWindowGLFW* window = new CWindowGLFW(this);
	window->Init();
	window->WaitEventsTimeout(m_EventMinDt);
	m_Window = window;
#endif
	CTriangleA* ta = new CTriangleA;
	ta->Init();
	CCubeA* ca = new CCubeA;
	ca->Init();
	CSphere* cs = new CSphere;
	cs->Init();
	//m_Objects.push_back(ta);
	//m_Objects.push_back(ca);
	m_Objects.push_back(cs);

	for (std::vector<CGEObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); it++)
	{
		(*it)->Render();
	}
}

void CGEApp::Release()
{
	m_AppTsartTime = 0;
	m_Frames = 0;

	if (m_Window)
	{
		m_Window->Release();
		delete m_Window;
	}
}

void CGEApp::Run()
{
	Init();
	int64 frameStart = m_AppTsartTime;
	int64 frameDt = 0;
	float dt = 0.0f;
	// Main Game Loop
	do
	{
		if (m_Frames > 0)
		{
			frameDt = frameStart;
			frameStart = CGETime::GetInstance()->GetTimeNow();
			frameDt -= frameStart;
			dt = - float(frameDt) / 1000.0f;
			if (dt < 0.0)
			{
				dt = 0.0;
			}
			// TODO: setup min max frame durations ans sleep if needed
		}
		// Update the game
		if (!UpdateAsynch(dt))
			break;
		// Draw the scene
		Render();
		// Sinchronize main (render) thread and
		// Update thread in case we are using multithreading
		Sinchronize();
		m_Frames++;
	} while (!m_Window->WindowShouldClose());

	Release();
}

bool CGEApp::Update(float dt)
{
	if (m_Window)
	{
		m_Window->Update(dt);
	}
	// TODO:  
	for (std::vector<CGEObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); it++)
	{
		(*it)->Update(dt);
	}

	//std::cout << "Frame Duration -> " << dt << " ms" << std::endl;

	return true;
}

void CGEApp::Render()
{
	if (m_EnableRender)
	{
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		// TODO: 
		for (std::vector<CGEObject*>::iterator it = m_Objects.begin(); it != m_Objects.end(); it++)
		{
			(*it)->Render();
		}
		
		if (m_Window)
		{
			// Should return after the frame was rendered, 
			// so all GPU<->CPU synchronizations has to be done in m_Window->Render()
			m_Window->Render();
		}
	}
}

void CGEApp::ProcessEvents()
{

}

bool CGEApp::UpdateAsynch(float dt)
{
	if (m_EnableUpdate)
	{
		// TODO: do this asynchronously
		m_LastUpdateResult = Update(dt);
		// 
	}
	return m_LastUpdateResult;
}

void CGEApp::Sinchronize()
{
	// TODO: Wait for CGEApp::Update(dt) to finish (in update threades)
}