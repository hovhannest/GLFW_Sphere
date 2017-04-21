#pragma once

#include "Utils\GEConfig.h"
#include "Interfaces\IReusable.h"
#include "Interfaces\IWindow.h"
#include <GL\glew.h>
#include "..\Sphere.h"
#include <vector>

class CGE2DScene;
class CGEObject;

class CGEApp
{
public:
	CGEApp();
	~CGEApp();

	FORCENOINLINE float GetEventMinDt() const { return m_EventMinDt; }
	FORCENOINLINE void SetEventMinDt(float val);
public:
	//
	virtual void	Init();
	virtual void	Release();

	virtual void	Run();

	//
	virtual bool Update(float dt);
	virtual void Render();
	
//	void AddEvent();
	void ProcessEvents();

	void ResetTimer() {};

protected:

	virtual bool UpdateAsynch(float dt);
	inline void Sinchronize();

protected:		

	bool						m_LastUpdateResult;
	IWindow*					m_Window;

	int64						m_AppTsartTime;
	int64						m_Frames;

	bool                        m_EnableRender;
	bool                        m_EnableUpdate;

	float						m_EventMinDt;

	std::vector<CGEObject*>		m_Objects;

	GLuint programID;
	GLuint handle[3];
	GLuint vaoHandle;
	std::vector<unsigned int> indices;

};

